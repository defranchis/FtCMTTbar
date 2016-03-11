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
  class SelectionModule_sub_post: public AnalysisModule {
  public:
    
    explicit SelectionModule_sub_post(Context & ctx);
    virtual bool process(Event & event);

  private:
    JetId jet_kinematic; 
    TopJetId topjet_kinematic;
    MuonId muid;
    std::string type;
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
      h_aftercuts_2_wp10, 
      h_aftercuts_2_wp11, 
      h_aftercutscorr_wp1, 
      h_aftercutscorr_wp2, 
      h_aftercutscorr_wp3, 
      h_aftercutscorr_wp4, 
      h_aftercutscorr_wp5, 
      h_aftercutscorr_wp6, 
      h_aftercutscorr_wp7, 
      h_aftercutscorr_wp8, 
      h_aftercutscorr_wp9, 
      h_aftercutscorr_wp10, 
      h_aftercutscorr_wp11,
      h_aftercuts_2_wp1_CSV, 
      h_aftercuts_2_wp2_CSV, 
      h_aftercuts_2_wp3_CSV, 
      h_aftercuts_2_wp4_CSV, 
      h_aftercuts_2_wp5_CSV, 
      h_aftercuts_2_wp6_CSV, 
      h_aftercuts_2_wp7_CSV, 
      h_aftercuts_2_wp8_CSV, 
      h_aftercuts_2_wp9_CSV, 
      h_aftercuts_2_wp10_CSV,
      h_aftercuts_2_wp11_CSV,     
      h_aftercuts_2_wp12_CSV,
      h_aftercuts_2_wp13_CSV,
      h_aftercuts_2_wp1_tau32, 
      h_aftercuts_2_wp2_tau32, 
      h_aftercuts_2_wp3_tau32, 
      h_aftercuts_2_wp4_tau32, 
      h_aftercuts_2_wp5_tau32, 
      h_aftercuts_2_wp6_tau32, 
      h_aftercuts_2_wp7_tau32, 
      h_aftercuts_2_wp8_tau32, 
      h_aftercuts_2_wp9_tau32, 
      h_aftercuts_2_wp10_tau32, 
      h_aftercuts_2_wp11_tau32,
      h_aftercuts_2_wp1_Mass,
      h_aftercuts_2_wp2_Mass, 
      h_aftercuts_2_wp3_Mass, 
      h_aftercuts_2_wp4_Mass, 
      h_aftercuts_2_wp5_Mass, 
      h_aftercuts_2_wp6_Mass, 
      h_aftercuts_2_wp7_Mass, 
      h_aftercuts_2_wp8_Mass, 
      h_aftercuts_2_wp9_Mass, 
      h_aftercuts_2_wp10_Mass, 
      h_aftercuts_2_wp11_Mass,
      h_aftercuts_2_wp1_Mass_tau32,
      h_aftercuts_2_wp2_Mass_tau32, 
      h_aftercuts_2_wp3_Mass_tau32, 
      h_aftercuts_2_wp4_Mass_tau32, 
      h_aftercuts_2_wp5_Mass_tau32, 
      h_aftercuts_2_wp6_Mass_tau32, 
      h_aftercuts_2_wp7_Mass_tau32, 
      h_aftercuts_2_wp8_Mass_tau32, 
      h_aftercuts_2_wp9_Mass_tau32, 
      h_aftercuts_2_wp10_Mass_tau32, 
      h_aftercuts_2_wp11_Mass_tau32, 
      h_aftercuts_2_wp1_Mass_CSV,
      h_aftercuts_2_wp2_Mass_CSV, 
      h_aftercuts_2_wp3_Mass_CSV, 
      h_aftercuts_2_wp4_Mass_CSV, 
      h_aftercuts_2_wp5_Mass_CSV, 
      h_aftercuts_2_wp6_Mass_CSV, 
      h_aftercuts_2_wp7_Mass_CSV, 
      h_aftercuts_2_wp8_Mass_CSV, 
      h_aftercuts_2_wp9_Mass_CSV, 
      h_aftercuts_2_wp10_Mass_CSV,
      h_aftercuts_2_wp11_Mass_CSV, 
      h_aftercuts_2_wp1_CSV_tau32,
      h_aftercuts_2_wp2_CSV_tau32, 
      h_aftercuts_2_wp3_CSV_tau32, 
      h_aftercuts_2_wp4_CSV_tau32, 
      h_aftercuts_2_wp5_CSV_tau32, 
      h_aftercuts_2_wp6_CSV_tau32, 
      h_aftercuts_2_wp7_CSV_tau32, 
      h_aftercuts_2_wp8_CSV_tau32, 
      h_aftercuts_2_wp9_CSV_tau32, 
      h_aftercuts_2_wp10_CSV_tau32,
      h_aftercuts_2_wp11_CSV_tau32,
      h_aftercuts_2_wp1_Mass_tau32_PT400,
      h_aftercuts_2_wp2_Mass_tau32_PT400, 
      h_aftercuts_2_wp3_Mass_tau32_PT400, 
      h_aftercuts_2_wp4_Mass_tau32_PT400, 
      h_aftercuts_2_wp5_Mass_tau32_PT400, 
      h_aftercuts_2_wp6_Mass_tau32_PT400, 
      h_aftercuts_2_wp7_Mass_tau32_PT400, 
      h_aftercuts_2_wp8_Mass_tau32_PT400, 
      h_aftercuts_2_wp9_Mass_tau32_PT400, 
      h_aftercuts_2_wp10_Mass_tau32_PT400, 
      h_aftercuts_2_wp11_Mass_tau32_PT400, 
      h_aftercuts_2_wp1_Mass_CSV_PT400,
      h_aftercuts_2_wp2_Mass_CSV_PT400, 
      h_aftercuts_2_wp3_Mass_CSV_PT400, 
      h_aftercuts_2_wp4_Mass_CSV_PT400, 
      h_aftercuts_2_wp5_Mass_CSV_PT400, 
      h_aftercuts_2_wp6_Mass_CSV_PT400, 
      h_aftercuts_2_wp7_Mass_CSV_PT400, 
      h_aftercuts_2_wp8_Mass_CSV_PT400, 
      h_aftercuts_2_wp9_Mass_CSV_PT400, 
      h_aftercuts_2_wp10_Mass_CSV_PT400,
      h_aftercuts_2_wp11_Mass_CSV_PT400,
      h_aftercuts_2_wp1_CSV_tau32_PT400,
      h_aftercuts_2_wp2_CSV_tau32_PT400, 
      h_aftercuts_2_wp3_CSV_tau32_PT400, 
      h_aftercuts_2_wp4_CSV_tau32_PT400, 
      h_aftercuts_2_wp5_CSV_tau32_PT400, 
      h_aftercuts_2_wp6_CSV_tau32_PT400, 
      h_aftercuts_2_wp7_CSV_tau32_PT400, 
      h_aftercuts_2_wp8_CSV_tau32_PT400, 
      h_aftercuts_2_wp9_CSV_tau32_PT400, 
      h_aftercuts_2_wp10_CSV_tau32_PT400,
      h_aftercuts_2_wp11_CSV_tau32_PT400,
      h_aftercuts_2_wp1_Mass_tau32_PT550,
      h_aftercuts_2_wp2_Mass_tau32_PT550, 
      h_aftercuts_2_wp3_Mass_tau32_PT550, 
      h_aftercuts_2_wp4_Mass_tau32_PT550, 
      h_aftercuts_2_wp5_Mass_tau32_PT550, 
      h_aftercuts_2_wp6_Mass_tau32_PT550, 
      h_aftercuts_2_wp7_Mass_tau32_PT550, 
      h_aftercuts_2_wp8_Mass_tau32_PT550, 
      h_aftercuts_2_wp9_Mass_tau32_PT550, 
      h_aftercuts_2_wp10_Mass_tau32_PT550, 
      h_aftercuts_2_wp11_Mass_tau32_PT550,
      h_aftercuts_2_wp1_Mass_CSV_PT550,
      h_aftercuts_2_wp2_Mass_CSV_PT550, 
      h_aftercuts_2_wp3_Mass_CSV_PT550, 
      h_aftercuts_2_wp4_Mass_CSV_PT550, 
      h_aftercuts_2_wp5_Mass_CSV_PT550, 
      h_aftercuts_2_wp6_Mass_CSV_PT550, 
      h_aftercuts_2_wp7_Mass_CSV_PT550, 
      h_aftercuts_2_wp8_Mass_CSV_PT550, 
      h_aftercuts_2_wp9_Mass_CSV_PT550, 
      h_aftercuts_2_wp10_Mass_CSV_PT550,
      h_aftercuts_2_wp11_Mass_CSV_PT550,
      h_aftercuts_2_wp1_CSV_tau32_PT550,
      h_aftercuts_2_wp2_CSV_tau32_PT550, 
      h_aftercuts_2_wp3_CSV_tau32_PT550, 
      h_aftercuts_2_wp4_CSV_tau32_PT550, 
      h_aftercuts_2_wp5_CSV_tau32_PT550, 
      h_aftercuts_2_wp6_CSV_tau32_PT550, 
      h_aftercuts_2_wp7_CSV_tau32_PT550, 
      h_aftercuts_2_wp8_CSV_tau32_PT550, 
      h_aftercuts_2_wp9_CSV_tau32_PT550, 
      h_aftercuts_2_wp10_CSV_tau32_PT550,
      h_aftercuts_2_wp11_CSV_tau32_PT550,
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

  };


  SelectionModule_sub_post::SelectionModule_sub_post(Context & ctx): selection(ctx, "selection") {
    
    type = ctx.get("dataset_type", "");
    //h_topjetsCMSTopTag = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetsCMSTopTag = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");

    

    jet_kinematic = PtEtaCut(30.0, 2.4);
    topjet_kinematic = PtEtaCut(400.0,2.4);
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1),MuonIso(0.12));
    //muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1));

    if (type != "DATA") pileup_SF.reset(new MCPileupReweight(ctx)); 


    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(ctx, jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));
    if (type == "DATA"){
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer15_25ns_L123_AK4PFchs_DATA));
      topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L123_AK8PFchs_DATA));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer15_25ns_L23_AK8PFchs_DATA));
    }
    else {
      jet_corrector.reset(new JetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_MC));
      jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Fall15_25ns_L123_AK4PFchs_MC));
      topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L123_AK8PFchs_MC));
      topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Fall15_25ns_L23_AK8PFchs_MC));
    }
    //cleanermodules.emplace_back(new TopJetCleaner(ctx, HEPTopTag(150)));
    //jetER_smearer.reset(new JetResolutionSmearer(ctx));
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

    h_nocuts.reset(new Hists_sub(ctx, "NoCuts"));
    h_aftercuts.reset(new Hists_sub(ctx, "AfterCuts"));
    h_aftercutscorr_wp1.reset(new Hists_sub(ctx, "AfterCutsCorr_wp1"));
    h_aftercutscorr_wp2.reset(new Hists_sub(ctx, "AfterCutsCorr_wp2"));
    h_aftercutscorr_wp3.reset(new Hists_sub(ctx, "AfterCutsCorr_wp3"));
    h_aftercutscorr_wp4.reset(new Hists_sub(ctx, "AfterCutsCorr_wp4"));
    h_aftercutscorr_wp5.reset(new Hists_sub(ctx, "AfterCutsCorr_wp5"));
    h_aftercutscorr_wp6.reset(new Hists_sub(ctx, "AfterCutsCorr_wp6"));
    h_aftercutscorr_wp7.reset(new Hists_sub(ctx, "AfterCutsCorr_wp7"));
    h_aftercutscorr_wp8.reset(new Hists_sub(ctx, "AfterCutsCorr_wp8"));
    h_aftercutscorr_wp9.reset(new Hists_sub(ctx, "AfterCutsCorr_wp9"));
    h_aftercutscorr_wp10.reset(new Hists_sub(ctx, "AfterCutsCorr_wp10"));
    h_aftercutscorr_wp11.reset(new Hists_sub(ctx, "AfterCutsCorr_wp11"));
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
    h_aftercuts_2_wp10.reset(new Hists_sub(ctx, "AfterCuts_2_wp10"));
    h_aftercuts_2_wp11.reset(new Hists_sub(ctx, "AfterCuts_2_wp11"));
    h_aftercuts_2_wp2_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_CSV"));
    h_aftercuts_2_wp4_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_CSV"));
    h_aftercuts_2_wp6_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_CSV"));
    h_aftercuts_2_wp8_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_CSV"));
    h_aftercuts_2_wp10_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_CSV"));
    h_aftercuts_2_wp11_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_CSV"));
    h_aftercuts_2_wp12_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp12_CSV"));
    h_aftercuts_2_wp13_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp13_CSV"));
    h_aftercuts_2_wp1_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_tau32"));
    h_aftercuts_2_wp2_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_tau32"));
    h_aftercuts_2_wp3_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_tau32"));
    h_aftercuts_2_wp4_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_tau32"));
    h_aftercuts_2_wp5_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_tau32"));
    h_aftercuts_2_wp6_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_tau32"));
    h_aftercuts_2_wp7_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_tau32"));
    h_aftercuts_2_wp8_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_tau32"));
    h_aftercuts_2_wp9_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_tau32"));
    h_aftercuts_2_wp10_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_tau32"));
    h_aftercuts_2_wp1_Mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass"));
    h_aftercuts_2_wp1_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_tau32"));
    h_aftercuts_2_wp2_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_tau32"));
    h_aftercuts_2_wp3_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_tau32"));
    h_aftercuts_2_wp4_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_tau32"));
    h_aftercuts_2_wp5_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_tau32"));
    h_aftercuts_2_wp6_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_tau32"));
    h_aftercuts_2_wp7_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_tau32"));
    h_aftercuts_2_wp8_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_tau32"));
    h_aftercuts_2_wp9_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_tau32"));
    h_aftercuts_2_wp10_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_tau32"));
    h_aftercuts_2_wp11_Mass_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_tau32"));
    h_aftercuts_2_wp1_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_CSV"));
    h_aftercuts_2_wp2_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_CSV"));
    h_aftercuts_2_wp3_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_CSV"));
    h_aftercuts_2_wp4_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_CSV"));
    h_aftercuts_2_wp5_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_CSV"));
    h_aftercuts_2_wp6_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_CSV"));
    h_aftercuts_2_wp7_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_CSV"));
    h_aftercuts_2_wp8_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_CSV"));
    h_aftercuts_2_wp9_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_CSV"));
    h_aftercuts_2_wp10_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_CSV"));
    h_aftercuts_2_wp11_Mass_CSV.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_CSV"));
    h_aftercuts_2_wp1_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_CSV_tau32"));
    h_aftercuts_2_wp2_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_CSV_tau32"));
    h_aftercuts_2_wp3_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_CSV_tau32"));
    h_aftercuts_2_wp4_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_CSV_tau32"));
    h_aftercuts_2_wp5_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_CSV_tau32"));
    h_aftercuts_2_wp6_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_CSV_tau32"));
    h_aftercuts_2_wp7_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_CSV_tau32"));
    h_aftercuts_2_wp8_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_CSV_tau32"));
    h_aftercuts_2_wp9_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_CSV_tau32"));
    h_aftercuts_2_wp10_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_CSV_tau32"));
    h_aftercuts_2_wp11_CSV_tau32.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_CSV_tau32"));    
    h_aftercuts_2_wp1_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_tau32_PT550"));
    h_aftercuts_2_wp2_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_tau32_PT550"));
    h_aftercuts_2_wp3_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_tau32_PT550"));
    h_aftercuts_2_wp4_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_tau32_PT550"));
    h_aftercuts_2_wp5_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_tau32_PT550"));
    h_aftercuts_2_wp6_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_tau32_PT550"));
    h_aftercuts_2_wp7_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_tau32_PT550"));
    h_aftercuts_2_wp8_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_tau32_PT550"));
    h_aftercuts_2_wp9_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_tau32_PT550"));
    h_aftercuts_2_wp10_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_tau32_PT550"));
    h_aftercuts_2_wp11_Mass_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_tau32_PT550"));
    h_aftercuts_2_wp1_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_CSV_PT550"));
    h_aftercuts_2_wp2_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_CSV_PT550"));
    h_aftercuts_2_wp3_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_CSV_PT550"));
    h_aftercuts_2_wp4_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_CSV_PT550"));
    h_aftercuts_2_wp5_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_CSV_PT550"));
    h_aftercuts_2_wp6_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_CSV_PT550"));
    h_aftercuts_2_wp7_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_CSV_PT550"));
    h_aftercuts_2_wp8_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_CSV_PT550"));
    h_aftercuts_2_wp9_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_CSV_PT550"));
    h_aftercuts_2_wp10_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_CSV_PT550"));
    h_aftercuts_2_wp11_Mass_CSV_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_CSV_PT550"));
    h_aftercuts_2_wp1_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_CSV_tau32_PT550"));
    h_aftercuts_2_wp2_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_CSV_tau32_PT550"));
    h_aftercuts_2_wp3_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_CSV_tau32_PT550"));
    h_aftercuts_2_wp4_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_CSV_tau32_PT550"));
    h_aftercuts_2_wp5_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_CSV_tau32_PT550"));
    h_aftercuts_2_wp6_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_CSV_tau32_PT550"));
    h_aftercuts_2_wp7_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_CSV_tau32_PT550"));
    h_aftercuts_2_wp8_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_CSV_tau32_PT550"));
    h_aftercuts_2_wp9_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_CSV_tau32_PT550"));
    h_aftercuts_2_wp10_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_CSV_tau32_PT550"));
    h_aftercuts_2_wp11_CSV_tau32_PT550.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_CSV_tau32_PT550"));
    h_aftercuts_2_wp1_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_tau32_PT400"));
    h_aftercuts_2_wp2_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_tau32_PT400"));
    h_aftercuts_2_wp3_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_tau32_PT400"));
    h_aftercuts_2_wp4_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_tau32_PT400"));
    h_aftercuts_2_wp5_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_tau32_PT400"));
    h_aftercuts_2_wp6_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_tau32_PT400"));
    h_aftercuts_2_wp7_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_tau32_PT400"));
    h_aftercuts_2_wp8_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_tau32_PT400"));
    h_aftercuts_2_wp9_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_tau32_PT400"));
    h_aftercuts_2_wp10_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_tau32_PT400"));
    h_aftercuts_2_wp11_Mass_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_tau32_PT400"));
    h_aftercuts_2_wp1_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_Mass_CSV_PT400"));
    h_aftercuts_2_wp2_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_Mass_CSV_PT400"));
    h_aftercuts_2_wp3_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_Mass_CSV_PT400"));
    h_aftercuts_2_wp4_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_Mass_CSV_PT400"));
    h_aftercuts_2_wp5_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_Mass_CSV_PT400"));
    h_aftercuts_2_wp6_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_Mass_CSV_PT400"));
    h_aftercuts_2_wp7_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_Mass_CSV_PT400"));
    h_aftercuts_2_wp8_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_Mass_CSV_PT400"));
    h_aftercuts_2_wp9_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_Mass_CSV_PT400"));
    h_aftercuts_2_wp10_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_Mass_CSV_PT400"));
    h_aftercuts_2_wp11_Mass_CSV_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_Mass_CSV_PT400"));
    h_aftercuts_2_wp1_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_CSV_tau32_PT400"));
    h_aftercuts_2_wp2_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_CSV_tau32_PT400"));
    h_aftercuts_2_wp3_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_CSV_tau32_PT400"));
    h_aftercuts_2_wp4_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_CSV_tau32_PT400"));
    h_aftercuts_2_wp5_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp5_CSV_tau32_PT400"));
    h_aftercuts_2_wp6_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp6_CSV_tau32_PT400"));
    h_aftercuts_2_wp7_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp7_CSV_tau32_PT400"));
    h_aftercuts_2_wp8_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp8_CSV_tau32_PT400"));
    h_aftercuts_2_wp9_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp9_CSV_tau32_PT400"));
    h_aftercuts_2_wp10_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp10_CSV_tau32_PT400"));
    h_aftercuts_2_wp11_CSV_tau32_PT400.reset(new Hists_sub(ctx, "AfterCuts_2_wp11_CSV_tau32_PT400"));

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


  bool SelectionModule_sub_post::process(Event & event) {

    if(!event.isRealData) pileup_SF->process(event);

    //clean events
    for(auto & m : cleanermodules){
      m->process(event);
    }
    
    jet_corrector->process(event);
    //if (type != "DATA"){
    //  jetER_smearer->process(event);
    //}
    jetlepton_cleaner->process(event);
    topjet_corrector->process(event);
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
    bool toptag_wp10 = 0;
    bool toptag_wp11 = 0;
    bool toptag_wp2_CSV = 0;
    bool toptag_wp4_CSV = 0;
    bool toptag_wp6_CSV = 0;
    bool toptag_wp8_CSV = 0;
    bool toptag_wp10_CSV = 0;
    bool toptag_wp11_CSV = 0;
    bool toptag_wp12_CSV = 0;
    bool toptag_wp13_CSV = 0;
    bool toptag_wp1_tau32 = 0;
    bool toptag_wp2_tau32 = 0;
    bool toptag_wp3_tau32 = 0;
    bool toptag_wp4_tau32 = 0;
    bool toptag_wp5_tau32 = 0;
    bool toptag_wp6_tau32 = 0;
    bool toptag_wp7_tau32 = 0;
    bool toptag_wp8_tau32 = 0;
    bool toptag_wp9_tau32 = 0;
    bool toptag_wp10_tau32 = 0;
    bool toptag_wp1_Mass = 0;
    bool toptag_wp1_Mass_CSV = 0;
    bool toptag_wp2_Mass_CSV = 0;
    bool toptag_wp3_Mass_CSV = 0;
    bool toptag_wp4_Mass_CSV = 0;
    bool toptag_wp5_Mass_CSV = 0;
    bool toptag_wp6_Mass_CSV = 0;
    bool toptag_wp7_Mass_CSV = 0;
    bool toptag_wp8_Mass_CSV = 0;
    bool toptag_wp9_Mass_CSV = 0;
    bool toptag_wp10_Mass_CSV = 0;
    bool toptag_wp11_Mass_CSV = 0;
    bool toptag_wp1_Mass_tau32 = 0;
    bool toptag_wp2_Mass_tau32 = 0;
    bool toptag_wp3_Mass_tau32 = 0;
    bool toptag_wp4_Mass_tau32 = 0;
    bool toptag_wp5_Mass_tau32 = 0;
    bool toptag_wp6_Mass_tau32 = 0;
    bool toptag_wp7_Mass_tau32 = 0;
    bool toptag_wp8_Mass_tau32 = 0;
    bool toptag_wp9_Mass_tau32 = 0;
    bool toptag_wp10_Mass_tau32 = 0;
    bool toptag_wp11_Mass_tau32 = 0;
    bool toptag_wp1_CSV_tau32 = 0;
    bool toptag_wp2_CSV_tau32 = 0;
    bool toptag_wp3_CSV_tau32 = 0;
    bool toptag_wp4_CSV_tau32 = 0;
    bool toptag_wp5_CSV_tau32 = 0;
    bool toptag_wp6_CSV_tau32 = 0;
    bool toptag_wp7_CSV_tau32 = 0;
    bool toptag_wp8_CSV_tau32 = 0;
    bool toptag_wp9_CSV_tau32 = 0;
    bool toptag_wp10_CSV_tau32 = 0;
    bool toptag_wp11_CSV_tau32 = 0;
    //bool MassCut = 0;
    //bool tau32 = 0;
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
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.44) toptag_wp1=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.54){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.79) toptag_wp2=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp3=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.61){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.76) toptag_wp4=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp5=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.8) toptag_wp6=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp7=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.75){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.39) toptag_wp8=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.86) toptag_wp9=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.87){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.089) toptag_wp10=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.89) toptag_wp11=1;}
	    }

	    //sequential ScaleFactors - N-1 
	    //Mass_CSV
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp1_Mass_CSV=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.79) toptag_wp2_Mass_CSV=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp3_Mass_CSV=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.76) toptag_wp4_Mass_CSV=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp5_Mass_CSV=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.80) toptag_wp6_Mass_CSV=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp7_Mass_CSV=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.39) toptag_wp8_Mass_CSV=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp9_Mass_CSV=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.089) toptag_wp10_Mass_CSV=1;}
	    }
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.89) toptag_wp11_Mass_CSV=1;}
	    }
	    //Mass_tau32
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.44) toptag_wp1_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.54) toptag_wp2_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp3_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.61) toptag_wp4_Mass_tau32=1; 
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp5_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp6_Mass_tau32=1; 
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp7_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.75) toptag_wp8_Mass_tau32=1; 
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.86) toptag_wp9_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.87) toptag_wp10_Mass_tau32=1;
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110 && topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp11_Mass_tau32=1;
	      
	    //CSV_tau32
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.44) toptag_wp1_CSV_tau32 =1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.54){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.79) toptag_wp2_CSV_tau32 =1;}
	    }
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp3_CSV_tau32 =1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.61){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.76) toptag_wp4_CSV_tau32 =1;}
	    }
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp5_CSV_tau32 =1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.80) toptag_wp6_CSV_tau32 =1;}
	    }
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp7_CSV_tau32 =1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.75){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.39) toptag_wp8_CSV_tau32 =1;}
	    }
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.86) toptag_wp9_CSV_tau32 =1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.87){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.089) toptag_wp10_CSV_tau32 =1;}
	    }
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69){
	      const std::vector<Jet> subjets=topjets->at(i).subjets();
	      for(unsigned int ii=0;ii<subjets.size();ii++){
		if(subjets[ii].btag_combinedSecondaryVertex()> 0.89) toptag_wp11_CSV_tau32 =1;}
	    }
	    //individual ScaleFactors
	    //Mass
	    if (topjets->at(i).softdropmass()<210 && topjets->at(i).softdropmass()>110) toptag_wp1_Mass=1;

	    //tau32
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.44) toptag_wp1_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.54) toptag_wp2_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.50) toptag_wp3_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.61) toptag_wp4_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.59) toptag_wp5_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp6_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) toptag_wp7_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.75) toptag_wp8_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.86) toptag_wp9_tau32=1;
	    if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.87) toptag_wp10_tau32=1;


	    //CSV

	    const std::vector<Jet> subjets=topjets->at(i).subjets();
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.79) toptag_wp2_CSV =1;}
	   
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.76) toptag_wp4_CSV =1;}
	   
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.80) toptag_wp6_CSV =1;}
	    
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.39) toptag_wp8_CSV =1;}
	  
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.089) toptag_wp10_CSV =1;}
	    for(unsigned int ii=0;ii<subjets.size();ii++){
	      if(subjets[ii].btag_combinedSecondaryVertex()> 0.89) toptag_wp11_CSV =1;}
            for(unsigned int ii=0;ii<subjets.size();ii++){
              if(subjets[ii].btag_combinedSecondaryVertex()> 0.605) toptag_wp12_CSV =1;}
            for(unsigned int ii=0;ii<subjets.size();ii++){
              if(subjets[ii].btag_combinedSecondaryVertex()> 0.97) toptag_wp13_CSV =1;}



	    //if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.44) tau32 = 1;
	    //if (topjets->at(i).softdropmass()>110) MassCut=1;

	  }
      }
    }
  
    bool keep = selection.passes(event);
    bool pass_trigger = trigger_sel->passes(event);
    //bool pass_met = met_sel->passes(event);
    //bool pass_htlep = htlep_sel->passes(event);

    h_nocuts->fill(event);
    if(keep && checkphi_pt && pass_trigger) 
      {
	bool pass_btag = btag_sel->passes(event);

	if(pass_btag)
	  {
	    //bool pass_twodcut = twodcut_sel->passes(event);
	    //if (pass_met &&  pass_htlep && pass_twodcut){
	      if (topjetpt > 400 && topjetpt <= 550) h_aftercuts_1_PT400_550->fill(event);
	      if (topjetpt > 550)h_aftercuts_1_PT550->fill(event);
	      h_aftercuts_1->fill(event);
	      if(toptag_wp1)
		{
		  h_aftercuts_2_wp1->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp1->fill(event);
		}
	      if(toptag_wp2)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp2->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp2->fill(event);
		}
	      if(toptag_wp3)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp3->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp3->fill(event);
		}
	      if(toptag_wp4)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp4->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp4->fill(event);
		}
	      if(toptag_wp5)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp5->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp5->fill(event);
		}
	      if(toptag_wp6)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp6->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp6->fill(event);
		}
	      if(toptag_wp7)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp7->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp7->fill(event);
		}
	      if(toptag_wp8)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp8->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp8->fill(event);
		}
	      if(toptag_wp9)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp9->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp9->fill(event);
		}
	      if(toptag_wp10)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp10->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp10->fill(event);
		}
	      if(toptag_wp11)
		{
		  topjet_corrector->process(event);
		  h_aftercuts_2_wp11->fill(event);
		  topjet23_corrector->process(event);
		  h_aftercutscorr_wp11->fill(event);
		}
	      topjet_corrector->process(event);
	      if(toptag_wp2_CSV){h_aftercuts_2_wp2_CSV->fill(event);}
	      if(toptag_wp4_CSV){h_aftercuts_2_wp4_CSV->fill(event);}
	      if(toptag_wp6_CSV){h_aftercuts_2_wp6_CSV->fill(event);}
	      if(toptag_wp8_CSV){h_aftercuts_2_wp8_CSV->fill(event);}
	      if(toptag_wp10_CSV){h_aftercuts_2_wp10_CSV->fill(event);}
	      if(toptag_wp11_CSV){h_aftercuts_2_wp11_CSV->fill(event);}
              if(toptag_wp12_CSV){h_aftercuts_2_wp12_CSV->fill(event);}
              if(toptag_wp13_CSV){h_aftercuts_2_wp13_CSV->fill(event);}
	      if(toptag_wp1_tau32){h_aftercuts_2_wp1_tau32->fill(event);}
	      if(toptag_wp2_tau32){h_aftercuts_2_wp2_tau32->fill(event);}
	      if(toptag_wp3_tau32){h_aftercuts_2_wp3_tau32->fill(event);}
	      if(toptag_wp4_tau32){h_aftercuts_2_wp4_tau32->fill(event);}
	      if(toptag_wp5_tau32){h_aftercuts_2_wp5_tau32->fill(event);}
	      if(toptag_wp6_tau32){h_aftercuts_2_wp6_tau32->fill(event);}
	      if(toptag_wp7_tau32){h_aftercuts_2_wp7_tau32->fill(event);}
	      if(toptag_wp8_tau32){h_aftercuts_2_wp8_tau32->fill(event);}
	      if(toptag_wp9_tau32){h_aftercuts_2_wp9_tau32->fill(event);}
	      if(toptag_wp10_tau32){h_aftercuts_2_wp10_tau32->fill(event);}
	      if(toptag_wp1_Mass){h_aftercuts_2_wp1_Mass->fill(event);}
	      if(toptag_wp1_Mass_CSV){h_aftercuts_2_wp1_Mass_CSV->fill(event);}
	      if(toptag_wp2_Mass_CSV){h_aftercuts_2_wp2_Mass_CSV->fill(event);}
	      if(toptag_wp3_Mass_CSV){h_aftercuts_2_wp3_Mass_CSV->fill(event);}
	      if(toptag_wp4_Mass_CSV){h_aftercuts_2_wp4_Mass_CSV->fill(event);}
	      if(toptag_wp5_Mass_CSV){h_aftercuts_2_wp5_Mass_CSV->fill(event);}
	      if(toptag_wp6_Mass_CSV){h_aftercuts_2_wp6_Mass_CSV->fill(event);}
	      if(toptag_wp7_Mass_CSV){h_aftercuts_2_wp7_Mass_CSV->fill(event);}
	      if(toptag_wp8_Mass_CSV){h_aftercuts_2_wp8_Mass_CSV->fill(event);}
	      if(toptag_wp9_Mass_CSV){h_aftercuts_2_wp9_Mass_CSV->fill(event);}
	      if(toptag_wp10_Mass_CSV){h_aftercuts_2_wp10_Mass_CSV->fill(event);}
	      if(toptag_wp11_Mass_CSV){h_aftercuts_2_wp11_Mass_CSV->fill(event);}
	      if(toptag_wp1_Mass_tau32){h_aftercuts_2_wp1_Mass_tau32->fill(event);}
	      if(toptag_wp2_Mass_tau32){h_aftercuts_2_wp2_Mass_tau32->fill(event);}
	      if(toptag_wp3_Mass_tau32){h_aftercuts_2_wp3_Mass_tau32->fill(event);}
	      if(toptag_wp4_Mass_tau32){h_aftercuts_2_wp4_Mass_tau32->fill(event);}
	      if(toptag_wp5_Mass_tau32){h_aftercuts_2_wp5_Mass_tau32->fill(event);}
	      if(toptag_wp6_Mass_tau32){h_aftercuts_2_wp6_Mass_tau32->fill(event);}
	      if(toptag_wp7_Mass_tau32){h_aftercuts_2_wp7_Mass_tau32->fill(event);}
	      if(toptag_wp8_Mass_tau32){h_aftercuts_2_wp8_Mass_tau32->fill(event);}
	      if(toptag_wp9_Mass_tau32){h_aftercuts_2_wp9_Mass_tau32->fill(event);}
	      if(toptag_wp10_Mass_tau32){h_aftercuts_2_wp10_Mass_tau32->fill(event);}
	      if(toptag_wp11_Mass_tau32){h_aftercuts_2_wp11_Mass_tau32->fill(event);}
	      if(toptag_wp1_CSV_tau32){h_aftercuts_2_wp1_CSV_tau32->fill(event);}
	      if(toptag_wp2_CSV_tau32){h_aftercuts_2_wp2_CSV_tau32->fill(event);}
	      if(toptag_wp3_CSV_tau32){h_aftercuts_2_wp3_CSV_tau32->fill(event);}
	      if(toptag_wp4_CSV_tau32){h_aftercuts_2_wp4_CSV_tau32->fill(event);}
	      if(toptag_wp5_CSV_tau32){h_aftercuts_2_wp5_CSV_tau32->fill(event);}
	      if(toptag_wp6_CSV_tau32){h_aftercuts_2_wp6_CSV_tau32->fill(event);}
	      if(toptag_wp7_CSV_tau32){h_aftercuts_2_wp7_CSV_tau32->fill(event);}
	      if(toptag_wp8_CSV_tau32){h_aftercuts_2_wp8_CSV_tau32->fill(event);}
	      if(toptag_wp9_CSV_tau32){h_aftercuts_2_wp9_CSV_tau32->fill(event);}
	      if(toptag_wp10_CSV_tau32){h_aftercuts_2_wp10_CSV_tau32->fill(event);}
	      if(toptag_wp11_CSV_tau32){h_aftercuts_2_wp11_CSV_tau32->fill(event);}
	      if (topjetpt > 400 && topjetpt <= 550)
		{
		  if(toptag_wp2_Mass_CSV){h_aftercuts_2_wp2_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp3_Mass_CSV){h_aftercuts_2_wp3_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp4_Mass_CSV){h_aftercuts_2_wp4_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp5_Mass_CSV){h_aftercuts_2_wp5_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp6_Mass_CSV){h_aftercuts_2_wp6_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp7_Mass_CSV){h_aftercuts_2_wp7_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp8_Mass_CSV){h_aftercuts_2_wp8_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp9_Mass_CSV){h_aftercuts_2_wp9_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp10_Mass_CSV){h_aftercuts_2_wp10_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp11_Mass_CSV){h_aftercuts_2_wp11_Mass_CSV_PT400->fill(event);}
		  if(toptag_wp1_Mass_tau32){h_aftercuts_2_wp1_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp2_Mass_tau32){h_aftercuts_2_wp2_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp3_Mass_tau32){h_aftercuts_2_wp3_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp4_Mass_tau32){h_aftercuts_2_wp4_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp5_Mass_tau32){h_aftercuts_2_wp5_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp6_Mass_tau32){h_aftercuts_2_wp6_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp7_Mass_tau32){h_aftercuts_2_wp7_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp8_Mass_tau32){h_aftercuts_2_wp8_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp9_Mass_tau32){h_aftercuts_2_wp9_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp10_Mass_tau32){h_aftercuts_2_wp10_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp11_Mass_tau32){h_aftercuts_2_wp11_Mass_tau32_PT400->fill(event);}
		  if(toptag_wp1_CSV_tau32){h_aftercuts_2_wp1_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp2_CSV_tau32){h_aftercuts_2_wp2_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp3_CSV_tau32){h_aftercuts_2_wp3_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp4_CSV_tau32){h_aftercuts_2_wp4_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp5_CSV_tau32){h_aftercuts_2_wp5_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp6_CSV_tau32){h_aftercuts_2_wp6_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp7_CSV_tau32){h_aftercuts_2_wp7_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp8_CSV_tau32){h_aftercuts_2_wp8_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp9_CSV_tau32){h_aftercuts_2_wp9_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp10_CSV_tau32){h_aftercuts_2_wp10_CSV_tau32_PT400->fill(event);}
		  if(toptag_wp11_CSV_tau32){h_aftercuts_2_wp11_CSV_tau32_PT400->fill(event);}
		}
	      if (topjetpt > 550)
		{
		  if(toptag_wp2_Mass_CSV){h_aftercuts_2_wp2_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp3_Mass_CSV){h_aftercuts_2_wp3_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp4_Mass_CSV){h_aftercuts_2_wp4_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp5_Mass_CSV){h_aftercuts_2_wp5_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp6_Mass_CSV){h_aftercuts_2_wp6_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp7_Mass_CSV){h_aftercuts_2_wp7_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp8_Mass_CSV){h_aftercuts_2_wp8_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp9_Mass_CSV){h_aftercuts_2_wp9_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp10_Mass_CSV){h_aftercuts_2_wp10_Mass_CSV_PT550->fill(event);}
		  if(toptag_wp11_Mass_CSV){h_aftercuts_2_wp11_Mass_CSV_PT550->fill(event);}

		  if(toptag_wp1_Mass_tau32){h_aftercuts_2_wp1_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp2_Mass_tau32){h_aftercuts_2_wp2_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp3_Mass_tau32){h_aftercuts_2_wp3_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp4_Mass_tau32){h_aftercuts_2_wp4_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp5_Mass_tau32){h_aftercuts_2_wp5_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp6_Mass_tau32){h_aftercuts_2_wp6_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp7_Mass_tau32){h_aftercuts_2_wp7_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp8_Mass_tau32){h_aftercuts_2_wp8_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp9_Mass_tau32){h_aftercuts_2_wp9_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp10_Mass_tau32){h_aftercuts_2_wp10_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp11_Mass_tau32){h_aftercuts_2_wp11_Mass_tau32_PT550->fill(event);}
		  if(toptag_wp1_CSV_tau32){h_aftercuts_2_wp1_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp2_CSV_tau32){h_aftercuts_2_wp2_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp3_CSV_tau32){h_aftercuts_2_wp3_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp4_CSV_tau32){h_aftercuts_2_wp4_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp5_CSV_tau32){h_aftercuts_2_wp5_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp6_CSV_tau32){h_aftercuts_2_wp6_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp7_CSV_tau32){h_aftercuts_2_wp7_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp8_CSV_tau32){h_aftercuts_2_wp8_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp9_CSV_tau32){h_aftercuts_2_wp9_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp10_CSV_tau32){h_aftercuts_2_wp10_CSV_tau32_PT550->fill(event);}
		  if(toptag_wp11_CSV_tau32){h_aftercuts_2_wp11_CSV_tau32_PT550->fill(event);}
		}
	    }
	//}
      }

    return keep;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(SelectionModule_sub_post)

}

