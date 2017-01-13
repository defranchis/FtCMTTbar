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
#include "UHH2/common/include/JetHists.h"



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
      h_aftercuts_2_wp6, 
      h_aftercuts_2_wp7, 
      h_aftercuts_2_wp8, 
      h_aftercuts_2_wp9, 

      h_aftercuts_2_wp1_Mass,

      h_aftercuts_2_wp6_Mass_tau32, 
      h_aftercuts_2_wp7_Mass_tau32, 
      h_aftercuts_2_wp8_Mass_tau32, 
      h_aftercuts_2_wp9_Mass_tau32,

      h_aftercuts_2_wp6_Mass_btag,
 
      h_aftercuts_2_wp1_PT400,
      h_aftercuts_2_wp2_PT400, 
      h_aftercuts_2_wp3_PT400, 
      h_aftercuts_2_wp4_PT400, 
      h_aftercuts_2_wp5_PT400,
      h_aftercuts_2_wp6_PT400,
      h_aftercuts_2_wp7_PT400, 
      h_aftercuts_2_wp8_PT400, 
      h_aftercuts_2_wp9_PT400, 
 
      h_aftercuts_2_wp1_PT550,
      h_aftercuts_2_wp2_PT550, 
      h_aftercuts_2_wp3_PT550, 
      h_aftercuts_2_wp4_PT550, 
      h_aftercuts_2_wp5_PT550,
      h_aftercuts_2_wp6_PT550,
      h_aftercuts_2_wp7_PT550, 
      h_aftercuts_2_wp8_PT550, 
      h_aftercuts_2_wp9_PT550,

      h_aftercuts_1_corr23, 

      h_aftercuts_1_PT400_550_corr23, 
      h_aftercuts_1_PT550_corr23, 

      h_aftercuts_2_wp1_corr23, 
      h_aftercuts_2_wp2_corr23, 
      h_aftercuts_2_wp3_corr23, 
      h_aftercuts_2_wp4_corr23, 
      h_aftercuts_2_wp5_corr23,
      h_aftercuts_2_wp6_corr23, 
      h_aftercuts_2_wp7_corr23, 
      h_aftercuts_2_wp8_corr23, 
      h_aftercuts_2_wp9_corr23, 

      h_aftercuts_2_wp1_tau32_corr23, 
      h_aftercuts_2_wp2_tau32_corr23, 
      h_aftercuts_2_wp3_tau32_corr23, 
      h_aftercuts_2_wp4_tau32_corr23, 
      h_aftercuts_2_wp5_tau32_corr23, 
      h_aftercuts_2_wp6_tau32_btag_corr23, 
      h_aftercuts_2_wp7_tau32_btag_corr23, 
      h_aftercuts_2_wp8_tau32_btag_corr23, 
      h_aftercuts_2_wp9_tau32_btag_corr23, 

      h_aftercuts_2_wp1_PT400_corr23,
      h_aftercuts_2_wp2_PT400_corr23, 
      h_aftercuts_2_wp3_PT400_corr23, 
      h_aftercuts_2_wp4_PT400_corr23, 
      h_aftercuts_2_wp5_PT400_corr23,
      h_aftercuts_2_wp6_PT400_corr23,
      h_aftercuts_2_wp7_PT400_corr23, 
      h_aftercuts_2_wp8_PT400_corr23, 
      h_aftercuts_2_wp9_PT400_corr23, 

      h_aftercuts_2_wp1_PT550_corr23,
      h_aftercuts_2_wp2_PT550_corr23, 
      h_aftercuts_2_wp3_PT550_corr23, 
      h_aftercuts_2_wp4_PT550_corr23, 
      h_aftercuts_2_wp5_PT550_corr23,
      h_aftercuts_2_wp6_PT550_corr23,
      h_aftercuts_2_wp7_PT550_corr23, 
      h_aftercuts_2_wp8_PT550_corr23, 
      h_aftercuts_2_wp9_PT550_corr23,

    //h_btageffAK8,

      h_aftercuts_3, 
      h_aftercuts;

    std::unique_ptr<JetCorrector> jet_corrector;
    //std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
    std::unique_ptr<TopJetCorrector> topjet_corrector;
    std::unique_ptr<TopJetCorrector> topjet23_corrector;
    //  std::unique_ptr<TopJetResolutionSmearer> topjetER_smearer;
    std::unique_ptr<TopJetLeptonDeltaRCleaner> topjetlepton_cleaner;
    std::unique_ptr<uhh2::AnalysisModule> muo_tight_noniso_SF;
    std::unique_ptr<AnalysisModule> btagwAK8;



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
    topjet_kinematic = PtEtaCut(170.0,2.4);
    //muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1),MuonIso(0.12));
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1));

    if (type != "DATA") pileup_SF.reset(new MCPileupReweight(ctx)); 


    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(ctx, jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));
    if (type == "DATA"){
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_DATA));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_DATA));
      topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK8PFchs_DATA));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L23_AK8PFchs_DATA));
    }
    else {
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_MC));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_MC));
      topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK8PFchs_MC));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L23_AK8PFchs_MC));
    }
    muo_tight_noniso_SF.reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/schumas/sframev6/CMSSW_7_6_3/src/UHH2/common/data/MuonID_Z_RunCD_Reco76X_Feb15.root","MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1",1, "tightID"));
    //cleanermodules.emplace_back(new TopJetCleaner(ctx, HEPTopTag(150)));
    //jetER_smearer.reset(new JetResolutionSmearer(ctx));
    jetlepton_cleaner->set_drmax(.4);
    //  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
    topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(0.8));
    // make the selection, step-by-step. Note that in most cases, no explicit
    // object id is passed, as the cleaners have removed the objects not passing the id already.

     if (version == "TTbar") {
       v_pre_modules.emplace_back(new TTbarGenProducer(ctx, "ttbargen", true));
       v_pre_modules.emplace_back(new TopPtWeight(ctx, "ttbargen", 0.156, -0.00137, "weight_ttbar", true));
     }
    //v_hists.emplace_back(new TopPtWeightHist(ctx, "TTbarReweight", "weight_ttbar"));
 


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
    h_aftercuts_2_wp6.reset(new Hists_sub(ctx, "AfterCuts_2_wp6"));
    h_aftercuts_2_wp7.reset(new Hists_sub(ctx, "AfterCuts_2_wp7"));
    h_aftercuts_2_wp8.reset(new Hists_sub(ctx, "AfterCuts_2_wp8"));
    h_aftercuts_2_wp9.reset(new Hists_sub(ctx, "AfterCuts_2_wp9"));

    h_aftercuts_2_wp1_Mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass"));
    h_aftercuts_2_wp6_Mass_btag.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_btag"));

    h_aftercuts_2_wp6_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_tau32"));
    h_aftercuts_2_wp7_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_tau32"));
    h_aftercuts_2_wp8_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_tau32"));
    h_aftercuts_2_wp9_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_tau32"));

    h_aftercuts_2_wp1_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_PT550"));
    h_aftercuts_2_wp2_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_PT550"));
    h_aftercuts_2_wp3_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_PT550"));
    h_aftercuts_2_wp4_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_PT550"));
    h_aftercuts_2_wp5_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_PT550"));
    h_aftercuts_2_wp6_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_PT550"));
    h_aftercuts_2_wp7_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_PT550"));
    h_aftercuts_2_wp8_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_PT550"));
    h_aftercuts_2_wp9_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_PT550"));

    h_aftercuts_2_wp1_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_PT400"));
    h_aftercuts_2_wp2_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_PT400"));
    h_aftercuts_2_wp3_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_PT400"));
    h_aftercuts_2_wp4_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_PT400"));
    h_aftercuts_2_wp5_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_PT400"));
    h_aftercuts_2_wp6_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_PT400"));
    h_aftercuts_2_wp7_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_PT400"));
    h_aftercuts_2_wp8_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_PT400"));
    h_aftercuts_2_wp9_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_PT400"));

    h_aftercuts_1_PT400_550_corr23.reset(new Hists_sub(ctx, "AfterCuts_1_PT400_550_corr23"));
    h_aftercuts_1_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_1_PT550_corr23"));

    h_aftercuts_1_corr23.reset(new Hists_sub(ctx, "AfterCuts_1_corr23"));

    h_aftercuts_2_wp1_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_corr23"));
    h_aftercuts_2_wp2_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_corr23"));
    h_aftercuts_2_wp3_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_corr23"));
    h_aftercuts_2_wp4_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_corr23"));
    h_aftercuts_2_wp5_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_corr23"));
    h_aftercuts_2_wp6_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_corr23"));
    h_aftercuts_2_wp7_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_corr23"));
    h_aftercuts_2_wp8_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_corr23"));
    h_aftercuts_2_wp9_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_corr23"));

    h_aftercuts_2_wp1_tau32_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_tau32_corr23"));
    h_aftercuts_2_wp2_tau32_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_tau32_corr23"));
    h_aftercuts_2_wp3_tau32_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_tau32_corr23"));
    h_aftercuts_2_wp4_tau32_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_tau32_corr23"));
    h_aftercuts_2_wp5_tau32_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_tau32_corr23"));
    h_aftercuts_2_wp6_tau32_btag_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_tau32_btag_corr23"));
    h_aftercuts_2_wp7_tau32_btag_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_tau32_btag_corr23"));
    h_aftercuts_2_wp8_tau32_btag_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_tau32_btag_corr23"));
    h_aftercuts_2_wp9_tau32_btag_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_tau32_btag_corr23"));

    h_aftercuts_2_wp1_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_PT550_corr23"));
    h_aftercuts_2_wp2_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_PT550_corr23"));
    h_aftercuts_2_wp3_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_PT550_corr23"));
    h_aftercuts_2_wp4_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_PT550_corr23"));
    h_aftercuts_2_wp5_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_PT550_corr23"));
    h_aftercuts_2_wp6_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_PT550_corr23"));
    h_aftercuts_2_wp7_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_PT550_corr23"));
    h_aftercuts_2_wp8_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_PT550_corr23"));
    h_aftercuts_2_wp9_PT550_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_PT550_corr23"));

    h_aftercuts_2_wp1_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_PT400_corr23"));
    h_aftercuts_2_wp2_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_PT400_corr23"));
    h_aftercuts_2_wp3_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_PT400_corr23"));
    h_aftercuts_2_wp4_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_PT400_corr23"));
    h_aftercuts_2_wp5_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_PT400_corr23"));
    h_aftercuts_2_wp6_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_PT400_corr23"));
    h_aftercuts_2_wp7_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_PT400_corr23"));
    h_aftercuts_2_wp8_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_PT400_corr23"));
    h_aftercuts_2_wp9_PT400_corr23.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_PT400_corr23"));

    //h_btageffAK8.reset(new BTagMCEfficiencyHists(ctx, "BTagMCEfficiencyHists",CSVBTag::WP_LOOSE,"jets"));

    btagwAK8.reset(new MCBTagScaleFactor(ctx, CSVBTag::WP_LOOSE, "jets","central","mujets","incl","MCBtagEfficiencies"));

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
    muo_tight_noniso_SF->process(event);
    //clean events
    for(auto & m : cleanermodules){
      m->process(event);
    }

    for (auto & mod : v_pre_modules) {
        mod->process(event);
    }

    std::vector<TopJet>* topjets = event.topjets;
    //std::cout << 1/topjets->at(0).JEC_factor_raw() << std::endl;

    
    topjet_corrector->process(event);
    jet_corrector->process(event);

    //std::cout << 1/topjets->at(0).JEC_factor_raw() << std::endl;
    //std::cout << "----------------------" << std::endl;

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
    bool toptag_wp6 = 0;
    bool toptag_wp7 = 0;
    bool toptag_wp8 = 0;
    bool toptag_wp9 = 0;

    bool toptag_wp6_Mass_btag = 0;

    bool toptag_wp6_Mass_tau32 = 0;
    bool toptag_wp7_Mass_tau32 = 0;
    bool toptag_wp8_Mass_tau32 = 0;
    bool toptag_wp9_Mass_tau32 = 0;

    bool toptag_wp6_tau32_btag = 0;
    bool toptag_wp7_tau32_btag = 0;
    bool toptag_wp8_tau32_btag = 0;
    bool toptag_wp9_tau32_btag = 0;

    bool toptag_wp1_tau32 = 0;
    bool toptag_wp2_tau32 = 0;
    bool toptag_wp3_tau32 = 0;
    bool toptag_wp4_tau32 = 0;
    bool toptag_wp5_tau32 = 0;

    bool toptag_wp1_Mass = 0;

    double topjetpt = 0.;

  

    if(selection.passes(event)){



      //Example to access top jets information and subjets

      std::vector<Muon>* muons = event.muons;

      
      for(unsigned int i=0;i<topjets->size();i++){
      
	TopJet topjet=topjets->at(i);
      
	double deltaphi = deltaPhi(topjet,muons->at(0));
	
	double pi = 3.14159265359;
	if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>170.)&&(fabs(topjets->at(i).eta())<2.4)) 
	  {

	    checkphi_pt = 1;
	    const std::vector<Jet> subjets=topjets->at(i).subjets();
	    JetId checkbtag=CSVBTag(CSVBTag::WP_LOOSE);
	    for(unsigned int m = 0; m < subjets.size(); m++)
	      {
	
		  
		 
		    
		    topjetpt=topjets->at(i).pt();
		    topjet23_corrector->process(event);
		    
		    LorentzVector subjet_sum;
		    for (const auto s : topjet.subjets()) {
		      subjet_sum += s.v4();
		    }
		   

		    double masstop = subjet_sum.M()*1/topjets->at(i).JEC_factor_raw();
		    








		    //std::cout << masstop << std::endl;
		    //ScaleFactors

		    ///////////////////CHS//////////////////
	

		    if (masstop<210 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.45) toptag_wp1=1; 
		    if (masstop<210 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.51) toptag_wp2=1;
		    if (masstop<210 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.60) toptag_wp3=1;
		    if (masstop<210 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp4=1;
		    if (masstop<210 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.84) toptag_wp5=1;
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp6=1;}
		    }
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.57) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp7=1;}
		    }
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.67) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp8=1;}
		    }
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.81) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp9=1;}
		    }
		 

		    //sequential ScaleFactors
		    // mass + tau32
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) {toptag_wp6_Mass_tau32=1;}
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.57) {toptag_wp7_Mass_tau32=1;}
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.67) {toptag_wp8_Mass_tau32=1;}
		    if (masstop<220 && masstop>105 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.81) {toptag_wp9_Mass_tau32=1;}
		    

		    // mass + btag
		    if (masstop<220 && masstop>105) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp6_Mass_btag=1;}
		    }
		  
		    // tau32 + btag
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp6_tau32_btag=1;}
		    }
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.57) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp7_tau32_btag=1;}
		    }
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.67) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp8_tau32_btag=1;}
		    }
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.81) {
		      const std::vector<Jet> subjets=topjets->at(i).subjets();
		      for(unsigned int ii=0;ii<subjets.size();ii++){
		    	if(subjets[ii].btag_combinedSecondaryVertex()> 0.46) toptag_wp9_tau32_btag=1;}
		    }


		    //individual ScaleFactors
		    //Mass
		    if (masstop<210 && masstop>105) toptag_wp1_Mass=1;
		    //tau32
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.45) toptag_wp1_tau32=1;
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.51) toptag_wp2_tau32=1;
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.60) toptag_wp3_tau32=1;
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp4_tau32=1;
		    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.84) toptag_wp5_tau32=1;

		  
	     
	      }
	  }
      }
    }
    bool keep = selection.passes(event);
    bool pass_trigger = trigger_sel->passes(event);
    bool pass_met = met_sel->passes(event);
    bool pass_htlep = htlep_sel->passes(event);

    topjet_corrector->process(event);

    for (auto & h : v_hists) {
      h->fill(event);
    }

    h_nocuts->fill(event);
    if(keep && checkphi_pt && pass_trigger) 
      {
      	bool pass_btag = btag_sel->passes(event);
	//h_btageffAK8->fill(event);

      	if(pass_btag)
      	  {
	    btagwAK8->process(event);
      	    bool pass_twodcut = twodcut_sel->passes(event);
      	    if (pass_met &&  pass_htlep && pass_twodcut){
      	      if (topjetpt > 400 && topjetpt <= 550) h_aftercuts_1_PT400_550->fill(event);
      	      if (topjetpt > 550)h_aftercuts_1_PT550->fill(event);

      	      h_aftercuts_1->fill(event);
	       
      	      if(toptag_wp1)h_aftercuts_2_wp1->fill(event);
      	      if(toptag_wp2)h_aftercuts_2_wp2->fill(event);
      	      if(toptag_wp3)h_aftercuts_2_wp3->fill(event);
      	      if(toptag_wp4)h_aftercuts_2_wp4->fill(event);
      	      if(toptag_wp5)h_aftercuts_2_wp5->fill(event);
      	      if(toptag_wp6)h_aftercuts_2_wp6->fill(event);
      	      if(toptag_wp7)h_aftercuts_2_wp7->fill(event);
      	      if(toptag_wp8)h_aftercuts_2_wp8->fill(event);
      	      if(toptag_wp9)h_aftercuts_2_wp9->fill(event);
 
      	      if(toptag_wp6_Mass_tau32)h_aftercuts_2_wp6_Mass_tau32->fill(event);
      	      if(toptag_wp7_Mass_tau32)h_aftercuts_2_wp7_Mass_tau32->fill(event);
      	      if(toptag_wp8_Mass_tau32)h_aftercuts_2_wp8_Mass_tau32->fill(event);
      	      if(toptag_wp9_Mass_tau32)h_aftercuts_2_wp9_Mass_tau32->fill(event);

      	      if(toptag_wp1_Mass)h_aftercuts_2_wp1_Mass->fill(event);
      	      if(toptag_wp6_Mass_btag)h_aftercuts_2_wp6_Mass_btag->fill(event);

      	      if (topjetpt > 400 && topjetpt <= 550)
      	      	{
      	      	  if(toptag_wp1)h_aftercuts_2_wp1_PT400->fill(event);
      	      	  if(toptag_wp2)h_aftercuts_2_wp2_PT400->fill(event);
      	      	  if(toptag_wp3)h_aftercuts_2_wp3_PT400->fill(event);
      	      	  if(toptag_wp4)h_aftercuts_2_wp4_PT400->fill(event);
      	      	  if(toptag_wp5)h_aftercuts_2_wp5_PT400->fill(event);
      	      	  if(toptag_wp6)h_aftercuts_2_wp6_PT400->fill(event);
      	      	  if(toptag_wp7)h_aftercuts_2_wp7_PT400->fill(event);
      	      	  if(toptag_wp8)h_aftercuts_2_wp8_PT400->fill(event);
      	      	  if(toptag_wp9)h_aftercuts_2_wp9_PT400->fill(event);
  
      	      	}
      	      if (topjetpt > 550)
      	      	{
      	      	  if(toptag_wp1)h_aftercuts_2_wp1_PT550->fill(event);
      	      	  if(toptag_wp2)h_aftercuts_2_wp2_PT550->fill(event);
      	      	  if(toptag_wp3)h_aftercuts_2_wp3_PT550->fill(event);
      	      	  if(toptag_wp4)h_aftercuts_2_wp4_PT550->fill(event);
      	      	  if(toptag_wp5)h_aftercuts_2_wp5_PT550->fill(event);
      	      	  if(toptag_wp6)h_aftercuts_2_wp6_PT550->fill(event);
      	      	  if(toptag_wp7)h_aftercuts_2_wp7_PT550->fill(event);
      	      	  if(toptag_wp8)h_aftercuts_2_wp8_PT550->fill(event);
      	      	  if(toptag_wp9)h_aftercuts_2_wp9_PT550->fill(event);
      	      	 
      	      	}
      	      topjet23_corrector->process(event);

      	      if (topjetpt > 400 && topjetpt <= 550) h_aftercuts_1_PT400_550_corr23->fill(event);
      	      if (topjetpt > 550)h_aftercuts_1_PT550_corr23->fill(event);

      	      h_aftercuts_1_corr23->fill(event);

      	      if(toptag_wp1)h_aftercuts_2_wp1_corr23->fill(event);
      	      if(toptag_wp2)h_aftercuts_2_wp2_corr23->fill(event);
      	      if(toptag_wp3)h_aftercuts_2_wp3_corr23->fill(event);
      	      if(toptag_wp4)h_aftercuts_2_wp4_corr23->fill(event);
      	      if(toptag_wp5)h_aftercuts_2_wp5_corr23->fill(event);
      	      if(toptag_wp6)h_aftercuts_2_wp6_corr23->fill(event);
      	      if(toptag_wp7)h_aftercuts_2_wp7_corr23->fill(event);
      	      if(toptag_wp8)h_aftercuts_2_wp8_corr23->fill(event);
      	      if(toptag_wp9)h_aftercuts_2_wp9_corr23->fill(event);

      	      if(toptag_wp1_tau32)h_aftercuts_2_wp1_tau32_corr23->fill(event);
      	      if(toptag_wp2_tau32)h_aftercuts_2_wp2_tau32_corr23->fill(event);
      	      if(toptag_wp3_tau32)h_aftercuts_2_wp3_tau32_corr23->fill(event);
      	      if(toptag_wp4_tau32)h_aftercuts_2_wp4_tau32_corr23->fill(event);
      	      if(toptag_wp5_tau32)h_aftercuts_2_wp5_tau32_corr23->fill(event);

      	      if(toptag_wp6_tau32_btag)h_aftercuts_2_wp6_tau32_btag_corr23->fill(event);
      	      if(toptag_wp7_tau32_btag)h_aftercuts_2_wp7_tau32_btag_corr23->fill(event);
      	      if(toptag_wp8_tau32_btag)h_aftercuts_2_wp8_tau32_btag_corr23->fill(event);
      	      if(toptag_wp9_tau32_btag)h_aftercuts_2_wp9_tau32_btag_corr23->fill(event);

      	      if(toptag_wp1_tau32)h_aftercuts_2_wp1_tau32_corr23->fill(event);
      	      if(toptag_wp6_tau32_btag)h_aftercuts_2_wp6_tau32_btag_corr23->fill(event);

      	      if (topjetpt > 400 && topjetpt <= 550)
      	      	{
      	      	  if(toptag_wp1)h_aftercuts_2_wp1_PT400_corr23->fill(event);
      	      	  if(toptag_wp2)h_aftercuts_2_wp2_PT400_corr23->fill(event);
      	      	  if(toptag_wp3)h_aftercuts_2_wp3_PT400_corr23->fill(event);
      	      	  if(toptag_wp4)h_aftercuts_2_wp4_PT400_corr23->fill(event);
      	      	  if(toptag_wp5)h_aftercuts_2_wp5_PT400_corr23->fill(event);
      	      	  if(toptag_wp6)h_aftercuts_2_wp6_PT400_corr23->fill(event);
      	      	  if(toptag_wp7)h_aftercuts_2_wp7_PT400_corr23->fill(event);
      	      	  if(toptag_wp8)h_aftercuts_2_wp8_PT400_corr23->fill(event);
      	      	  if(toptag_wp9)h_aftercuts_2_wp9_PT400_corr23->fill(event);
      	      	}
      	      if (topjetpt > 550)
      	      	{
      	      	  if(toptag_wp1)h_aftercuts_2_wp1_PT550_corr23->fill(event);
      	      	  if(toptag_wp2)h_aftercuts_2_wp2_PT550_corr23->fill(event);
      	      	  if(toptag_wp3)h_aftercuts_2_wp3_PT550_corr23->fill(event);
      	      	  if(toptag_wp4)h_aftercuts_2_wp4_PT550_corr23->fill(event);
      	      	  if(toptag_wp5)h_aftercuts_2_wp5_PT550_corr23->fill(event);
      	      	  if(toptag_wp6)h_aftercuts_2_wp6_PT550_corr23->fill(event);
      	      	  if(toptag_wp7)h_aftercuts_2_wp7_PT550_corr23->fill(event);
      	      	  if(toptag_wp8)h_aftercuts_2_wp8_PT550_corr23->fill(event);
      	      	  if(toptag_wp9)h_aftercuts_2_wp9_PT550_corr23->fill(event);
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

