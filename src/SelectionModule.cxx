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
#include "UHH2/common/include/TTbarReconstruction.h"

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

    uhh2::Event::Handle<std::vector<TopJet> > h_topjetsCMSTopTag;
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetssoftdrop;
 
  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_nocuts, h_aftercuts;


    std::vector<std::unique_ptr<AnalysisModule>> cleanermodules;
    AndSelection selection;
  
  };


  SelectionModule::SelectionModule(Context & ctx): selection(ctx, "selection") {


    h_topjetsCMSTopTag = ctx.declare_event_input<std::vector<TopJet> >("slimmedJetsAK8_CMSTopTag");
    h_topjetssoftdrop = ctx.declare_event_input<std::vector<TopJet> >("patJetsAk8CHSJetsSoftDropPacked_daughters");
    h_topjetsCMSTopTag = ctx.declare_event_output<std::vector<TopJet> >("slimmedJetsAK8_CMSTopTag");
    h_topjetssoftdrop = ctx.declare_event_output<std::vector<TopJet> >("patJetsAk8CHSJetsSoftDropPacked_daughters");

    

    jet_kinematic = PtEtaCut(50.0, 2.4);
    topjet_kinematic = PtEtaCut(350.0,2.4);
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(20.0, 2.4));
    
    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));
    cleanermodules.emplace_back(new TopJetCleaner(CMSTopTag()));
    
    // make the selection, step-by-step. Note that in most cases, no explicit
    // object id is passed, as the cleaners have removed the objects not passing the id already.
    selection.add<NMuonSelection>("nm == 1", 1, 1);
    selection.add<NJetSelection>("nj >= 2", 2);
    selection.add<NTopJetSelection>("ntj >= 1", 1);

    h_nocuts.reset(new Hists2(ctx, "NoCuts"));
    h_aftercuts.reset(new Hists2(ctx, "AfterCuts"));

  }


  bool SelectionModule::process(Event & event) {


    for(auto & m : cleanermodules){
      m->process(event);
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
	if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>350.)&&(fabs(topjets->at(i).eta())<2.4)) checkphi_pt = 1;

	
      
	//std::cout << "pt of topjet " << i << " is " << topjet.pt() << std::endl;
          

	/*const std::vector<Jet> subjets=topjet.subjets();
      
	//std::cout << "this topjet has " << subjets.size() << " subjets" << std::endl;

	for(unsigned int ii=0;ii<subjets.size();ii++){

        Jet subjet=subjets[ii];
        
	//std::cout << "Subjet " << ii << " has pt " << subjet.pt() << std::endl;
	*/
      
      
      }

    }
   
  
    
    // note that always both selections are tested, even if we could
    // short-circuit after mu_selection is passed. This is done
    // to ensure that both cutflow histograms are filled.
    bool keep = selection.passes(event);

    h_nocuts->fill(event);

    if(keep && checkphi_pt) h_aftercuts->fill(event);

    return keep;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(SelectionModule)

}
