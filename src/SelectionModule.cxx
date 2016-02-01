#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/FtCMTTbar/include/Hists2.h"
#include "UHH2/FtCMTTbar/include/FtCMTTbarSelections.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/FtCMTTbar/include/FtCMTTbarUtils.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/MCWeight.h"


using namespace std;
using namespace uhh2;



namespace uhh2examples {

  /** \brief Another analysis example of an AnalysisModule
   * 
   * In contrast to ExampleModule, this class uses more code from 'common' to achieve
   * similar effects.
   * 
   * It implements a preselection of
   *   - at least one lepton (electron or muon) with pt > 20, |eta| < 2.4 (electrons: |eta| < 2.5), using the tight id for
   *     muons and the medium cut-based id for electrons.
   *   - at least two jets with pt > 30, eta < 2.4
   *   - at least one b-tagged jet with above kinematics with loose csv b-tag
   * 
   * In the output, only leptons passing the id and jets with pt > 30 GeV and eta < 2.4 are kept.
   */
  class SelectionModule: public AnalysisModule {
  public:
    
    explicit SelectionModule(Context & ctx);
    virtual bool process(Event & event);

  private:
    JetId jet_kinematic; 
    TopJetId topjet_kinematic;
    MuonId muid;
    std::string type;
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetsCMSTopTag;
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetssoftdrop;
 
  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_nocuts, h_aftercuts_1, h_aftercuts_2, h_aftercuts_3, h_aftercuts_4, h_aftercuts;
    

    std::unique_ptr<JetCorrector> jet_corrector;
    std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
    std::unique_ptr<TopJetCorrector> topjet_corrector;
    //  std::unique_ptr<TopJetResolutionSmearer> topjetER_smearer;
    std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;

    std::vector<std::unique_ptr<AnalysisModule>> cleanermodules;
    AndSelection selection;
    std::unique_ptr<Selection> trigger_sel;
    std::unique_ptr<Selection> twodcut_sel;
    std::unique_ptr<Selection> met_sel;
    std::unique_ptr<Selection> htlep_sel;
    std::unique_ptr<Selection> btag_sel;
    std::unique_ptr<Selection> lumi_selection;
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
  };


  SelectionModule::SelectionModule(Context & ctx): selection(ctx, "selection") {
    
    type = ctx.get("dataset_type", "");
    h_topjetsCMSTopTag = ctx.declare_event_input<std::vector<TopJet> >("patJetsHepTopTagCHSPacked_daughters");
    h_topjetssoftdrop = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    h_topjetsCMSTopTag = ctx.declare_event_output<std::vector<TopJet> >("patJetsHepTopTagCHSPacked_daughters");
    h_topjetssoftdrop = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");

    

    jet_kinematic = PtEtaCut(30.0, 2.4);
    topjet_kinematic = PtEtaCut(150.0,2.4);
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1),MuonIso(0.12));

    if (type != "DATA") pileup_SF.reset(new MCPileupReweight(ctx)); 

    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));
    cleanermodules.emplace_back(new TopJetCleaner(HEPTopTag(150)));
    if (type == "DATA"){
      jet_corrector.reset(new JetCorrector(ctx,JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
    jetlepton_cleaner.reset(new JetLeptonCleaner(ctx,JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
    topjet_corrector.reset(new TopJetCorrector(ctx,JERFiles::Summer15_25ns_L123_AK8PFchs_DATA));
    }
    else {
    jet_corrector.reset(new JetCorrector(ctx,JERFiles::Summer15_25ns_L123_AK4PFchs_MC));
    jetlepton_cleaner.reset(new JetLeptonCleaner(ctx,JERFiles::Summer15_25ns_L123_AK4PFchs_MC));
    topjet_corrector.reset(new TopJetCorrector(ctx,JERFiles::Summer15_25ns_L123_AK8PFchs_MC));
    }

    jetER_smearer.reset(new JetResolutionSmearer(ctx));
    jetlepton_cleaner->set_drmax(.4);

    //  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
    topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(1.5));
    // make the selection, step-by-step. Note that in most cases, no explicit
    // object id is passed, as the cleaners have removed the objects not passing the id already.

    const std::string triggername(ctx.get("triggername", "NotSet"));

    //    selection.add<NElectronSelection>("ne == 0", 0, 0);
    selection.add<NMuonSelection>("nm == 1", 1, 1);
    selection.add<NJetSelection>("nj >= 2", 2);
    selection.add<NTopJetSelection>("ntj >= 1", 1);

    h_nocuts.reset(new Hists2(ctx, "NoCuts"));
    h_aftercuts.reset(new Hists2(ctx, "AfterCuts"));
    h_aftercuts_1.reset(new Hists2(ctx, "AfterCuts_1"));
    h_aftercuts_2.reset(new Hists2(ctx, "AfterCuts_2"));
    h_aftercuts_3.reset(new Hists2(ctx, "AfterCuts_3"));
    h_aftercuts_4.reset(new Hists2(ctx, "AfterCuts_4"));
    if (type == "DATA"){
      std::cout << "Running on Data, using lumi selection!" << std::endl;
      lumi_selection.reset(new LumiSelection(ctx));
    }

    trigger_sel = make_unique<TriggerSelection>("HLT_Mu45_eta2p1_v*");
    twodcut_sel.reset(new TwoDCut(.4, 25.));
    met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
    htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
    btag_sel.reset(new NMuonBTagSelection(1));


  }


  bool SelectionModule::process(Event & event) {

    if(!event.isRealData) pileup_SF->process(event);

    //clean events
    for(auto & m : cleanermodules){
      m->process(event);
    }
    jet_corrector->process(event);
    if (type != "DATA"){
      jetER_smearer->process(event);
    }
    jetlepton_cleaner->process(event);
    topjet_corrector->process(event);
    //  topjetER_smearer->process(event);
    topjetlepton_cleaner->process(event);

    if (lumi_selection.get() && !lumi_selection->passes(event)) {
        return false;
    }

    bool checkphi_pt=0;
    if(selection.passes(event)){

      //Example to access top jets information and subjets
      std::vector<TopJet>* topjets = event.topjets;
      std::vector<Muon>* muons = event.muons;



      for(unsigned int i=0;i<topjets->size();i++){
      
	TopJet topjet=topjets->at(i);
      
	double deltaphi = deltaPhi(topjet,muons->at(0));
	double pi = 3.14159265359;
	if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>150.)&&(fabs(topjets->at(i).eta())<2.4)) checkphi_pt = 1;
      
      }

    }
    bool keep = selection.passes(event);
    bool pass_trigger = trigger_sel->passes(event);
    bool pass_met = met_sel->passes(event);
    bool pass_htlep = htlep_sel->passes(event);
    
    //bool pass_twodcut =1;
    h_nocuts->fill(event);

    if(keep && checkphi_pt)
      {
	
	h_aftercuts_1->fill(event);

	if(pass_trigger)
	  {
	    h_aftercuts_2->fill(event);
	
	  
	    bool pass_twodcut = 1;//twodcut_sel->passes(event);

	    if(pass_twodcut) 
	      {

		h_aftercuts_3->fill(event);

		bool pass_btag = btag_sel->passes(event);

		if(pass_btag)
		  {

		    h_aftercuts_4->fill(event);

		    if(pass_met && pass_htlep)
		      {
			h_aftercuts->fill(event);
		      }
		  }
	      }
	  }
      }
     

    return keep;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(SelectionModule)

}
