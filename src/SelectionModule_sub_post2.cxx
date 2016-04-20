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
#include "UHH2/FtCMTTbar/include/Hists_sub.h"
#include "UHH2/FtCMTTbar/include/FtCMTTbarSelections.h"
#include "UHH2/common/include/TTbarReconstruction.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/FtCMTTbar/include/FtCMTTbarUtils.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/FtCMTTbar/include/FtCMTTbarCommonModules.h"
#include "UHH2/JetMETObjects/interface/FactorizedJetCorrector.h"




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
  class SelectionModule_sub_post2: public AnalysisModule {
  public:
    
    explicit SelectionModule_sub_post2(Context & ctx);
    virtual bool process(Event & event);

  private:
    JetId jet_kinematic; 
    TopJetId topjet_kinematic;
    MuonId muid;
    std::string type;
    std::string version;
    //uhh2::Event::Handle<std::vector<TopJet> > h_topjetsCMSTopTag;
    //uhh2::Event::Handle<std::vector<TopJet> > h_topjetssoftdrop;
 
  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_nocuts, 
      h_aftercuts_1, 
      h_aftercuts_1_PT400_550, 
      h_aftercuts_1_PT550, 
      h_aftercuts_2_wp1, 
      h_aftercuts_2_wp2, 
      h_aftercuts_2_wp3, 
      h_aftercuts_2_wp4, 
      h_aftercuts_2_wp5, 
      h_aftercutscorr_wp1, 
      h_aftercutscorr_wp2, 
      h_aftercutscorr_wp3, 
      h_aftercutscorr_wp4, 
      h_aftercutscorr_wp5,
      h_aftercuts_2_wp1_tau32, 
      h_aftercuts_2_wp2_tau32, 
      h_aftercuts_2_wp3_tau32, 
      h_aftercuts_2_wp4_tau32, 
      h_aftercuts_2_wp5_tau32, 
      h_aftercuts_2_wp1_Mass,
      h_aftercuts_2_wp2_Mass, 
      h_aftercuts_2_wp3_Mass, 
      h_aftercuts_2_wp4_Mass, 
      h_aftercuts_2_wp5_Mass,
      h_aftercuts_2_wp1_Mass_tau32_PT400,
      h_aftercuts_2_wp2_Mass_tau32_PT400, 
      h_aftercuts_2_wp3_Mass_tau32_PT400, 
      h_aftercuts_2_wp4_Mass_tau32_PT400, 
      h_aftercuts_2_wp5_Mass_tau32_PT400,
      h_aftercuts_2_wp1_Mass_tau32_PT550,
      h_aftercuts_2_wp2_Mass_tau32_PT550, 
      h_aftercuts_2_wp3_Mass_tau32_PT550, 
      h_aftercuts_2_wp4_Mass_tau32_PT550, 
      h_aftercuts_2_wp5_Mass_tau32_PT550,
  
      h_aftercuts_3, 
      h_aftercuts;

    std::unique_ptr<JetCorrector> jet_corrector;
    //std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
    std::unique_ptr<TopJetCorrector> topjet_corrector;
    std::unique_ptr<TopJetCorrector> topjet23_corrector;
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
    std::vector<std::unique_ptr<AnalysisModule>> v_pre_modules;
    std::vector<std::unique_ptr<Hists>> v_hists;
  };


  SelectionModule_sub_post2::SelectionModule_sub_post2(Context & ctx): selection(ctx, "selection") {
    
    type = ctx.get("dataset_type", "");
    version = ctx.get("dataset_version", "");
    //h_topjetsCMSTopTag = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetsCMSTopTag = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");

    

    jet_kinematic = PtEtaCut(30.0, 2.4);
    topjet_kinematic = PtEtaCut(400.0,2.4);
    //muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1),MuonIso(0.12));
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1));

    if (type != "DATA") pileup_SF.reset(new MCPileupReweight(ctx)); 


    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(ctx, jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));
    if (type == "DATA"){
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
      //topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK8PFchs_DATA));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L23_AK8PFchs_DATA));
    }
    else {
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_MC));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_MC));
      //topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK8PFchs_MC));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L23_AK8PFchs_MC));
    }
    //cleanermodules.emplace_back(new TopJetCleaner(ctx, HEPTopTag(150)));
    //jetER_smearer.reset(new JetResolutionSmearer(ctx));
    jetlepton_cleaner->set_drmax(.4);
    //  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
    topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(0.8));
    // make the selection, step-by-step. Note that in most cases, no explicit
    // object id is passed, as the cleaners have removed the objects not passing the id already.

    //if (version == "TTbar") {
    //  v_pre_modules.emplace_back(new TTbarGenProducer(ctx, "ttbargen", false));
    //  v_pre_modules.emplace_back(new TopPtWeight(ctx, "ttbargen", 0.156, -0.00137, "weight_ttbar", false));
    //  v_hists.emplace_back(new TopPtWeightHist(ctx, "TTbarReweight", "weight_ttbar"));
    //}
    
 


    const std::string triggername(ctx.get("triggername", "NotSet"));

    //    selection.add<NElectronSelection>("ne == 0", 0, 0);
    selection.add<NMuonSelection>("nm == 1", 1, 1);
    selection.add<NJetSelection>("nj >= 2", 2);
    selection.add<NTopJetSelection>("ntj >= 1", 1);

    h_nocuts.reset(new Hists_sub(ctx, "NoCuts"));
    h_aftercuts.reset(new Hists_sub(ctx, "AfterCuts"));
    h_aftercuts_1_PT400_550.reset(new Hists_sub(ctx, "AfterCuts_1_PT400_550"));
    h_aftercuts_1_PT550.reset(new Hists_sub(ctx, "AfterCuts_1_PT550"));
    h_aftercuts_1.reset(new Hists_sub(ctx, "AfterCuts_1"));
    h_aftercuts_2_wp1.reset(new Hists_sub(ctx, "AfterCuts_2_wp1"));
    h_aftercuts_2_wp2.reset(new Hists_sub(ctx, "AfterCuts_2_wp2"));
    h_aftercuts_2_wp3.reset(new Hists_sub(ctx, "AfterCuts_2_wp3"));
    h_aftercuts_2_wp4.reset(new Hists_sub(ctx, "AfterCuts_2_wp4"));
    h_aftercuts_2_wp5.reset(new Hists_sub(ctx, "AfterCuts_2_wp5"));
    h_aftercuts_2_wp1_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_tau32"));
    h_aftercuts_2_wp2_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_tau32"));
    h_aftercuts_2_wp3_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_tau32"));
    h_aftercuts_2_wp4_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_tau32"));
    h_aftercuts_2_wp5_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_tau32"));
    h_aftercuts_2_wp1_Mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass"));
    h_aftercuts_2_wp1_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_tau32_PT550"));
    h_aftercuts_2_wp2_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_tau32_PT550"));
    h_aftercuts_2_wp3_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_tau32_PT550"));
    h_aftercuts_2_wp4_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_tau32_PT550"));
    h_aftercuts_2_wp5_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_tau32_PT550"));
    h_aftercuts_2_wp1_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_tau32_PT400"));
    h_aftercuts_2_wp2_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_tau32_PT400"));
    h_aftercuts_2_wp3_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_tau32_PT400"));
    h_aftercuts_2_wp4_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_tau32_PT400"));
    h_aftercuts_2_wp5_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_tau32_PT400"));

    if (type == "DATA"){
      //  std::cout << "Running on Data, using lumi selection!" << std::endl;
      lumi_selection.reset(new LumiSelection(ctx));
    }

    trigger_sel = uhh2::make_unique<TriggerSelection>("HLT_Mu45_eta2p1_v*");
    twodcut_sel.reset(new TwoDCut(.4, 25.));
    met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
    htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
    btag_sel.reset(new NMuonBTagSelection(1));
  }


  bool SelectionModule_sub_post2::process(Event & event) {

    if(!event.isRealData) pileup_SF->process(event);

    //clean events
    for(auto & m : cleanermodules){
      m->process(event);
    }

    topjet23_corrector->process(event);
    jet_corrector->process(event);

    //if (type != "DATA"){
    //  jetER_smearer->process(event);
    //}

    jetlepton_cleaner->process(event);

    //topjet_corrector->process(event);
    //  topjetER_smearer->process(event);

    topjetlepton_cleaner->process(event);

    if (lumi_selection.get() && !lumi_selection->passes(event)) {
      return false;
    }

    //bool btagged = 0;
    bool checkphi_pt=0;
    bool toptag_wp1 = 0;
    bool toptag_wp2 = 0;
    bool toptag_wp3 = 0;
    bool toptag_wp4 = 0;
    bool toptag_wp5 = 0;
    bool toptag_wp1_tau32 = 0;
    bool toptag_wp2_tau32 = 0;
    bool toptag_wp3_tau32 = 0;
    bool toptag_wp4_tau32 = 0;
    bool toptag_wp5_tau32 = 0;
    bool toptag_wp1_Mass = 0;
    double topjetpt = 0.;


    if(selection.passes(event)){



      //Example to access top jets information and subjets
      std::vector<TopJet>* topjets = event.topjets;
      std::vector<Muon>* muons = event.muons;

      
      for(unsigned int i=0;i<topjets->size();i++){
      
	TopJet topjet=topjets->at(i);
      
	double deltaphi = deltaPhi(topjet,muons->at(0));
	
	double pi = 3.14159265359;
	if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>400.)&&(fabs(topjets->at(i).eta())<2.4)) 
	  {
	    checkphi_pt = 1;
	    topjetpt=topjets->at(i).pt();

	    //ScaleFactors
	    if (i > 0) std::cout << "Topjet " << i << std::endl;
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.45) toptag_wp1=1;
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp2=1;
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp3=1;
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.68) toptag_wp4=1;
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.83) toptag_wp5=1;
	    
	    //individual ScaleFactors
	    //Mass
	    if (topjets->at(i).v4().M()<220 && topjets->at(i).v4().M()>105) toptag_wp1_Mass=1;

	    //tau32
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.45) toptag_wp1_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp2_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp3_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.68) toptag_wp4_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.83) toptag_wp5_tau32=1;
	  }
      }
    }
  
    bool keep = selection.passes(event);
    bool pass_trigger = trigger_sel->passes(event);
    bool pass_met = met_sel->passes(event);
    bool pass_htlep = htlep_sel->passes(event);

    h_nocuts->fill(event);
    if(keep && checkphi_pt && pass_trigger) 
      {
	bool pass_btag = btag_sel->passes(event);

	if(pass_btag)
	  {
	    bool pass_twodcut = twodcut_sel->passes(event);
	    if (pass_met &&  pass_htlep && pass_twodcut){
	      if (topjetpt > 400 && topjetpt <= 550) h_aftercuts_1_PT400_550->fill(event);
	      if (topjetpt > 550)h_aftercuts_1_PT550->fill(event);
	      h_aftercuts_1->fill(event);
	      if(toptag_wp1)
		{
		  h_aftercuts_2_wp1->fill(event);
		}
	      if(toptag_wp2)
		{
		  h_aftercuts_2_wp2->fill(event);
		}
	      if(toptag_wp3)
		{
		  h_aftercuts_2_wp3->fill(event);
		}
	      if(toptag_wp4)
		{
		  h_aftercuts_2_wp4->fill(event);
		}
	      if(toptag_wp5)
		{
		  h_aftercuts_2_wp5->fill(event);
		}
	  
	    
	    
	      if(toptag_wp1_tau32){h_aftercuts_2_wp1_tau32->fill(event);}
	      if(toptag_wp2_tau32){h_aftercuts_2_wp2_tau32->fill(event);}
	      if(toptag_wp3_tau32){h_aftercuts_2_wp3_tau32->fill(event);}
	      if(toptag_wp4_tau32){h_aftercuts_2_wp4_tau32->fill(event);}
	      if(toptag_wp5_tau32){h_aftercuts_2_wp5_tau32->fill(event);}

	      if(toptag_wp1_Mass){h_aftercuts_2_wp1_Mass->fill(event);}

	      if (topjetpt > 400 && topjetpt <= 550)
		{
		  if(toptag_wp1){h_aftercuts_2_wp1_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp2){h_aftercuts_2_wp2_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp3){h_aftercuts_2_wp3_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp4){h_aftercuts_2_wp4_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp5){h_aftercuts_2_wp5_Mass_tau32_PT400->fill(event);}
		}
	      if (topjetpt > 550)
		{
		  if(toptag_wp1){h_aftercuts_2_wp1_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp2){h_aftercuts_2_wp2_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp3){h_aftercuts_2_wp3_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp4){h_aftercuts_2_wp4_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp5){h_aftercuts_2_wp5_Mass_tau32_PT550->fill(event);}
		}
	    }
	  }
      }

    return keep;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(SelectionModule_sub_post2)

}

