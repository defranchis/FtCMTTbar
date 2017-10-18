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
#include "UHH2/common/include/TTbarGen.h"

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
  class SelectionModule_sub_post_bbtag: public AnalysisModule {
  public:
    
    explicit SelectionModule_sub_post_bbtag(Context & ctx);
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
      h_aftercuts_1_mass,
      h_aftercuts_1_prunedmass,
      h_aftercuts_1_PT400_550, 
      h_aftercuts_1_PT550, 
      h_aftercuts_2_wp1, 
      h_aftercuts_2_wp2, 
      h_aftercuts_2_wp3, 
      h_aftercuts_2_wp4, 
      h_aftercuts_2_wp1_mass, 
      h_aftercuts_2_wp2_mass, 
      h_aftercuts_2_wp3_mass,
      h_aftercuts_2_wp4_mass,
      h_aftercuts_2_wp1_prunedmass, 
      h_aftercuts_2_wp2_prunedmass, 
      h_aftercuts_2_wp3_prunedmass, 
      h_aftercuts_2_wp4_prunedmass, 
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


  SelectionModule_sub_post_bbtag::SelectionModule_sub_post_bbtag(Context & ctx): selection(ctx, "selection") {
    
    type = ctx.get("dataset_type", "");
    version = ctx.get("dataset_version", "");
    //h_topjetsCMSTopTag = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_input<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetsCMSTopTag = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");
    //h_topjetssoftdrop = ctx.declare_event_output<std::vector<TopJet> >("patJetsCa15CHSJetsSoftDropPacked_daughters");

    

    jet_kinematic = PtEtaCut(30.0, 2.4);
    // topjet_kinematic = PtEtaCut(300.0,2.4);
    muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1),MuonIso(0.12));

    topjet_kinematic = PtEtaCut(250.0,2.4);



    //muid = AndId<Muon>(MuonIDTight(), PtEtaCut(50.0, 2.1));

    if (type != "DATA") pileup_SF.reset(new MCPileupReweight(ctx)); 


    // clean the objects:
    cleanermodules.emplace_back(new JetCleaner(ctx, jet_kinematic));
    cleanermodules.emplace_back(new MuonCleaner(muid));


    // if (type == "DATA"){
    //   jet_corrector.reset(new JetCorrector(ctx, JERFiles::Spring16_25ns_L123_AK4PFchs_DATA));
    //   jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Spring16_25ns_L123_AK4PFchs_DATA));
    //   topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Spring16_25ns_L123_AK8PFchs_DATA));
    //   topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Spring16_25ns_L23_AK8PFchs_DATA));
    // }
    // else {
    //   jet_corrector.reset(new JetCorrector(ctx, JERFiles::Spring16_25ns_L123_AK4PFchs_MC));
    //   jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Spring16_25ns_L123_AK4PFchs_MC));
    //   topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Spring16_25ns_L123_AK8PFchs_MC));
    //   topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Spring16_25ns_L23_AK8PFchs_MC));
    // }


    if (type == "DATA"){

        if ( (version=="Data1") || (version=="Data2") || (version=="Data3") || (version=="Data4") ){
            
            jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFchs_DATA));
            jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFchs_DATA));
            topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFchs_DATA));
            topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFchs_DATA));

        }

        else if ( (version=="Data5") || (version=="Data6") ){
            
            jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFchs_DATA));
            jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFchs_DATA));
            topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFchs_DATA));
            topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFchs_DATA));

        }

        else if ( version=="Data7" ){
            
            jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFchs_DATA));
            jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFchs_DATA));
            topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFchs_DATA));
            topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFchs_DATA));

        }

        else if ( (version=="Data8") || (version=="Data9") ){
            
            jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA));
            jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA));
            topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFchs_DATA));
            topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFchs_DATA));

        }


    } // if data

    else {

        jet_corrector.reset(new JetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC));
        jetlepton_cleaner.reset(new JetLeptonCleaner(ctx, JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC));
        topjet_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_L123_AK8PFchs_MC));
        topjet23_corrector.reset(new TopJetCorrector(ctx, JERFiles::Summer16_23Sep2016_V4_L123_AK8PFchs_MC));
    }



    //cleanermodules.emplace_back(new TopJetCleaner(ctx, HEPTopTag(150)));
    //jetER_smearer.reset(new JetResolutionSmearer(ctx));
    jetlepton_cleaner->set_drmax(.4);
    //  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
    topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(0.8));
    // make the selection, step-by-step. Note that in most cases, no explicit
    // object id is passed, as the cleaners have removed the objects not passing the id already.

    if (version == "TTbar") {
      v_pre_modules.emplace_back(new TTbarGenProducer(ctx, "ttbargen", true));
      // v_pre_modules.emplace_back(new TopPtWeight(ctx, "ttbargen", 0.156, -0.00137, "weight_ttbar", true));
      v_pre_modules.emplace_back(new TopPtWeight(ctx, "ttbargen", 0.0615, -0.0005, "weight_ttbar", true));
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
    h_aftercuts_1_mass.reset(new Hists_sub(ctx, "AfterCuts_1_mass"));
    h_aftercuts_1_prunedmass.reset(new Hists_sub(ctx, "AfterCuts_1_prunedmass"));
    h_aftercuts_2_wp1.reset(new Hists_sub(ctx, "AfterCuts_2_wp1"));
    h_aftercuts_2_wp2.reset(new Hists_sub(ctx, "AfterCuts_2_wp2"));
    h_aftercuts_2_wp3.reset(new Hists_sub(ctx, "AfterCuts_2_wp3"));
    h_aftercuts_2_wp4.reset(new Hists_sub(ctx, "AfterCuts_2_wp4"));
    h_aftercuts_2_wp1_mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_mass"));
    h_aftercuts_2_wp2_mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_mass"));
    h_aftercuts_2_wp3_mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_mass"));
    h_aftercuts_2_wp4_mass.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_mass"));
    h_aftercuts_2_wp1_prunedmass.reset(new Hists_sub(ctx, "AfterCuts_2_wp1_prunedmass"));
    h_aftercuts_2_wp2_prunedmass.reset(new Hists_sub(ctx, "AfterCuts_2_wp2_prunedmass"));
    h_aftercuts_2_wp3_prunedmass.reset(new Hists_sub(ctx, "AfterCuts_2_wp3_prunedmass"));
    h_aftercuts_2_wp4_prunedmass.reset(new Hists_sub(ctx, "AfterCuts_2_wp4_prunedmass"));

    if (type == "DATA"){
      //  std::cout << "Running on Data, using lumi selection!" << std::endl;
      lumi_selection.reset(new LumiSelection(ctx));
    }

    trigger_sel = uhh2::make_unique<TriggerSelection>("HLT_Mu50_v*");
    twodcut_sel.reset(new TwoDCut(.4, 25.));
    met_sel.reset(new METCut(50., std::numeric_limits<double>::infinity()));
    htlep_sel.reset(new HTlepCut(150., std::numeric_limits<double>::infinity()));
    btag_sel.reset(new NMuonBTagSelection(1));
  }


  bool SelectionModule_sub_post_bbtag::process(Event & event) {

    if(!event.isRealData) pileup_SF->process(event);

    //clean events
    for(auto & m : cleanermodules){
      m->process(event);
    }

    for (auto & mod : v_pre_modules) {
        mod->process(event);
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
    bool bbtag_wp1 = 0;
    bool bbtag_wp2 = 0;
    bool bbtag_wp3 = 0;
    bool bbtag_wp4 = 0;
    bool higgsmass = 0;
    bool prunedmass = 0;
    unsigned int takehighestpt = 0;
    // unsigned int takehighestmass = 0;

    //bool MassCut = 0;
    // bool tau32 = 0;
    bool tau21 = false;
    double topjetpt = 0.;


    if(selection.passes(event)){

      //Example to access top jets information and subjets
      std::vector<TopJet>* topjets = event.topjets;
      std::vector<Muon>* muons = event.muons;
      std::vector<Jet>* jets = event.jets;

      if(topjets->size()>1)
	{
	  double ptTopJet[topjets->size()];

	  for(unsigned int j=0;j<topjets->size();j++){
	    ptTopJet[j] = topjets->at(j).pt();
	  }

	  int tempPT = 0;
	  // int tempMass = 0;
	  
	  for(unsigned int k=0;k<topjets->size();k++)
	    {
	      if(ptTopJet[k]>tempPT){tempPT=ptTopJet[k]; takehighestpt = k;}	    
	    }


	  // for(unsigned int k=0;k<topjets->size();k++){

          //       if( topjets->at(k).prunedmass() > tempMass ){
          //           tempMass = topjets->at(k).prunedmass();
          //           takehighestmass = k;
          //       }	    
                
          // }


	} 



      
      for(unsigned int i=0;i<topjets->size();i++){
	
	if(topjets->size()>1)
	  {
	    if (takehighestpt!=i) continue;
	    // if (takehighestmass!=i) continue;
	  }

	TopJet topjet=topjets->at(i);
      
	double deltaphi = deltaPhi(topjet,muons->at(0));
	
	double pi = 3.14159265359;
	if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>250.)&&(fabs(topjets->at(i).eta())<2.4)) 
	// if(deltaphi>2*pi/3 &&(topjets->at(i).pt()>300.)&&(fabs(topjets->at(i).eta())<2.4)) 
	  {
	    checkphi_pt = 1;
	    topjetpt=topjets->at(i).pt();
	    if (i > 2) std::cout << "!!!!!!!!!!!!!!!!!! Topjet " << i << std::endl;
	    //ScaleFactors
	    
	    if(topjets->at(i).btag_BoostedDoubleSecondaryVertexAK8()> 0.3 ) bbtag_wp1=1;
	    if(topjets->at(i).btag_BoostedDoubleSecondaryVertexAK8()> 0.6 ) bbtag_wp2=1;
	    if(topjets->at(i).btag_BoostedDoubleSecondaryVertexAK8()> 0.8 ) bbtag_wp3=1;
	    if(topjets->at(i).btag_BoostedDoubleSecondaryVertexAK8()> 0.9 ) bbtag_wp4=1;
	    if(70 < topjets->at(i).softdropmass() && topjets->at(i).softdropmass()< 200) higgsmass = 1;
	    // if(70 < topjets->at(i).prunedmass() && topjets->at(i).prunedmass()< 200) prunedmass = 1;
	    if(50 < topjets->at(i).prunedmass() && topjets->at(i).prunedmass()< 200) prunedmass = 1;
	  }

	// if (topjets->at(i).tau3()/topjets->at(i).tau2()< 0.69) tau32 = 1;
	// if (topjets->at(i).tau2()/topjets->at(i).tau1()< 0.55) tau21 = true;
	if (topjets->at(i).tau2()/topjets->at(i).tau1()< 0.6) tau21 = true;
	//if (topjets->at(i).softdropmass()>110) MassCut=1;

        /* looking for AK04 jet in the hadronic hemisphere */


        bool checkak4 = 0 ;

        // JetId my_checkbtag = CSVBTag( CSVBTag::WP_LOOSE );

        for (unsigned int j = 0; j<jets->size(); ++j){

            // if ( ! my_checkbtag(jets->at(i), event) ) continue;

            double deltaphijet = deltaPhi(jets->at(j),muons->at(0));
            double deltarjettop = deltaR(jets->at(j),topjets->at(i));

            if(deltaphijet>2*pi/3 && deltarjettop > 0.8) {
                checkak4 =1;
                break;
            }

        } // loop on AK04 jets
        
        if (!checkak4) checkphi_pt = 0;

      } // loop in AK08 jets

    }// if passed selection
  
  
    bool keep = selection.passes(event);
    bool pass_trigger = trigger_sel->passes(event);
    //bool pass_met = met_sel->passes(event);
    //bool pass_htlep = htlep_sel->passes(event);


    for (auto & h : v_hists) {
      h->fill(event);
    }

    h_nocuts->fill(event);
    if(keep && checkphi_pt && pass_trigger) 
      {
	bool pass_btag = btag_sel->passes(event);

	// if(pass_btag && tau32)
	if(pass_btag && tau21)
	// if(pass_btag)
	  {
	    //bool pass_twodcut = twodcut_sel->passes(event);
	    //if (pass_met &&  pass_htlep && pass_twodcut){
	      if (topjetpt > 300 && topjetpt <= 550) h_aftercuts_1_PT400_550->fill(event);
	      if (topjetpt > 550)h_aftercuts_1_PT550->fill(event);
	      h_aftercuts_1->fill(event);
	      if(bbtag_wp1)
		{
		  h_aftercuts_2_wp1->fill(event);

		}
	      if(bbtag_wp2)
		{
		  h_aftercuts_2_wp2->fill(event);
		}
	      if(bbtag_wp3)
		{
		  h_aftercuts_2_wp3->fill(event);
		}
	      if(bbtag_wp4)
		{
		  h_aftercuts_2_wp4->fill(event);
		}
	      if(higgsmass)
		{
		  h_aftercuts_1_mass->fill(event);
		  if(bbtag_wp1)
		    {
		      h_aftercuts_2_wp1_mass->fill(event);

		    }
		  if(bbtag_wp2)
		    {
		      h_aftercuts_2_wp2_mass->fill(event);
		    }
		  if(bbtag_wp3)
		    {
		      h_aftercuts_2_wp3_mass->fill(event);
		    }
		  if(bbtag_wp4)
		    {
		      h_aftercuts_2_wp4_mass->fill(event);
		    }
		}
	      if(prunedmass)
		{
		  h_aftercuts_1_prunedmass->fill(event);
		  if(bbtag_wp1)
		    {
		      h_aftercuts_2_wp1_prunedmass->fill(event);

		    }
		  if(bbtag_wp2)
		    {
		      h_aftercuts_2_wp2_prunedmass->fill(event);
		    }
		  if(bbtag_wp3)
		    {
		      h_aftercuts_2_wp3_prunedmass->fill(event);
		    }
		  if(bbtag_wp4)
		    {
		      h_aftercuts_2_wp4_prunedmass->fill(event);
		    }
		}
	      //}
	}
      }

    return keep;
  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the ExampleModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(SelectionModule_sub_post_bbtag)

}

