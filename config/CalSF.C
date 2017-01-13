#include <TMath.h>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TString.h"
#include <iostream>
#include "TLegend.h"
#include "TCanvas.h"
#include <vector>
#include "TArray.h"
#include <TText.h>

//EXECUTION OF CalSF.C IN THE FOLDER WHERE THE ROOT FILES ARE STORED. EXECUTION WITH root -l CalSF.C
//THE SCALEFACTORS ARE STORED IN Scalefactors.txt

//BACKGROUND FILES

vector<TString> Files_MC(vector<TString> list)
{
  list.push_back("uhh2.AnalysisModuleRunner.MC.TTbar.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-10to50.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_t-channel.root"); 
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_tW_antitop.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_tW_top.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.WJets.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.QCD.root");
  return list;
}

//NAMES OF THE DIFFERENT BACKGROUNDS

vector<TString> Files_BKG(vector<TString> list)
{
  list.push_back("DY");
  list.push_back("ST"); 
  list.push_back("WJets");
  list.push_back("QCD");
  return list;
}

//SELECTIONS STEP FOR THE DIFFERENT WORKING POINTS

vector<TString> WP_2(vector<TString> list)
{
  list.push_back("AfterCuts_2_wp1");
  list.push_back("AfterCuts_2_wp2");
  //list.push_back("AfterCuts_2_wp1_mass");
  //list.push_back("AfterCuts_2_wp2_mass");
  return list;
}

//NAME OF THE WORKING POINTS

vector<TString> WP(vector<TString> list)
{
  list.push_back("wp1");
  list.push_back("wp2");
  return list;
}

//DEFINITION OF THE WORKING POINTS

vector<TString> LEGEND(vector<TString> list)
{
  list.push_back("btag_BoostedDoubleSecondaryVertexAK8> 0.3");
  list.push_back("btag_BoostedDoubleSecondaryVertexAK8> 0.6");
  return list;
}

void CalSF()
{
  std::ofstream output("./Scalefactors.txt");
  vector<TString> files_mc, files_bkg, wp_2, wp, legend;
  files_mc=Files_MC(files_mc);
  files_bkg=Files_BKG(files_bkg);
  wp_2=WP_2(wp_2);
  wp=WP(wp);
  legend=LEGEND(legend);
  
  gStyle->SetOptStat("");
  gStyle->SetLabelFont(42);
  gStyle->SetLabelSize(0.04, "X");
  gStyle->SetLabelSize(0.04, "Y");
  gStyle->SetTitleSize(0.04, "X");
  gStyle->SetTitleSize(0.04, "Y");
  gStyle->SetTitleFont(42);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(2);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadLeftMargin(0.16);
  gStyle->SetPadRightMargin(0.02);
  gStyle->SetPadTopMargin(0.065);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetOptStat("");
  gStyle->SetTitleH(0.04);

  for(unsigned int n = 0; n < wp_2.size(); n++)
    {
      TH1F *h_ttbar_2;
      TH1F *h_ttbar_3;
      TH1F *h_mc_2;
      TH1F *h_mc_3;
      TH1F *h_DY_50_2;
      TH1F *h_DY_50_3;
      TH1F *h_ST_50_2;
      TH1F *h_ST_50_3;
      TH1F *h_WJets_50_2;
      TH1F *h_WJets_50_3;
      TH1F *h_QCD_50_2;
      TH1F *h_QCD_50_3;
      TH1F *h_data_3;
      TH1F *h_data_2;
      TH1 *h_data_3_new;
      TH1 *h_data_2_new;
      TH1 *h_data_3_new_err;
      TH1 *h_data_2_new_err;
      TH1 *h_ttbar_2_new;
      TH1 *h_ttbar_3_new;
      TH1 *h_data_eff_new;
      TH1 *h_mc_eff_new;
      TH1 *h_data_3_new2;
      TH1 *h_data_2_new2;
      TH1 *h_ttbar_2_new2;
      TH1 *h_ttbar_3_new2;
      TH1 *h_data_eff_new2;
      TH1 *h_data_eff_new_err;
      TH1 *h_mc_eff_new2;
      TH1 *h_SF_new;
      TH1 *h_SF_new2;
      TH1 *h_SF_new_err_DY;
      TH1 *h_SF_new_err_ST;
      TH1 *h_SF_new_err_WJets;
      TH1 *h_SF_new_err_QCD;
      TH1F *h_data_eff= new TH1F("mc_data", "mc_data",100, 0., 2000.);
      TH1F *h_data_err= new TH1F("mc_data", "mc_data",100, 0., 2000.);
      TH1F *h_mc_eff= new TH1F("mc_eff", "mc_eff",100, 0., 2000.);      
      TH1F *h_mc_eff_err= new TH1F("mc_eff", "mc_eff",100, 0., 2000.);
      TH1F *h_SF_err=new TH1F("SF_"+wp[n], "SF_"+wp[n],100, 0., 2000.);
      TH1F *h_SF=new TH1F("SF_"+wp[n], "SF_"+wp[n],100, 0., 2000.);

      //RUN OVER ALL WORKING POINTS AND CALCULATE THE SCALE FACTORS

      for(unsigned int m = 0; m < files_mc.size(); m++)
	{
	  TFile *file= new TFile(files_mc[m]);
	  file->cd();
	  if (m == 0) 
	    { 
	      gDirectory->GetObject("AfterCuts_1/PTTop",h_ttbar_2 );
	      gDirectory->GetObject(wp_2[n]+"/PTTop",h_ttbar_3 );
	    }
	  if (m == 1) 
	    { 
	      gDirectory->GetObject("AfterCuts_1/PTTop",h_mc_2 );
	      gDirectory->GetObject(wp_2[n]+"/PTTop",h_mc_3 );
	    }
	  if (m > 1) 
	    { 
	      TH1F *h_tmp_2; gDirectory->GetObject("AfterCuts_1/PTTop",h_tmp_2 );
	      TH1F *h_tmp_3;gDirectory->GetObject(wp_2[n]+"/PTTop",h_tmp_3 );
	      h_mc_2->Add(h_tmp_2);
	      h_mc_3->Add(h_tmp_3);
	    }
	}
  
      TFile *file= new TFile("uhh2.AnalysisModuleRunner.DATA.Data.root");
      file->cd();
      gDirectory->GetObject("AfterCuts_1/PTTop",h_data_2 );
      gDirectory->GetObject(wp_2[n]+"/PTTop",h_data_3 );
      h_data_2->Add(h_mc_2, -1);
      h_data_3->Add(h_mc_3, -1);
      Double_t xbins[4] = {0.,400,550,2000};
      h_data_2_new=h_data_2->Rebin(3,"h_data_2_new",xbins);
      h_data_3_new=h_data_3->Rebin(3,"h_data_3_new",xbins);
      h_data_eff_new=h_data_eff->Rebin(3,"h_data_eff_new",xbins);
      h_mc_eff_new=h_mc_eff->Rebin(3,"h_mc_eff_new",xbins);
      h_SF_new=h_SF->Rebin(3,"h_SF_new",xbins);
      h_ttbar_3_new=h_ttbar_3->Rebin(3,"h_ttbar_3_new",xbins);
      h_ttbar_2_new=h_ttbar_2->Rebin(3,"h_ttbar_2_new",xbins);
      h_data_eff_new->Divide(h_data_3_new,h_data_2_new,1,1,"b");
      h_mc_eff_new->Divide(h_ttbar_3_new,h_ttbar_2_new,1,1,"b");
      h_SF_new->Divide(h_data_eff_new, h_mc_eff_new,1,1,"");

      Double_t xbins2[2] = {0., 2000};
      h_data_2_new2=h_data_2->Rebin(1,"h_data_2_new2",xbins2);
      h_data_3_new2=h_data_3->Rebin(1,"h_data_3_new2",xbins2);
      h_data_eff_new2=h_data_eff->Rebin(1,"h_data_eff_new2",xbins2);
      h_mc_eff_new2=h_mc_eff->Rebin(1,"h_mc_eff_new2",xbins2);
      h_SF_new2=h_SF->Rebin(1,"h_SF_new2",xbins2);
      h_ttbar_3_new2=h_ttbar_3->Rebin(1,"h_ttbar_3_new2",xbins2);
      h_ttbar_2_new2=h_ttbar_2->Rebin(1,"h_ttbar_2_new2",xbins2);
      h_data_eff_new2->Divide(h_data_3_new2,h_data_2_new2,1,1,"b");
      h_mc_eff_new2->Divide(h_ttbar_3_new2,h_ttbar_2_new2,1,1,"b");
      h_SF_new2->Divide(h_data_eff_new2, h_mc_eff_new2,1,1,"");

      h_SF_new->SetYTitle("Scale Factor");
      h_SF_new->SetXTitle("PT of TopJet [GeV]");
      h_SF_new->SetTitle("");
      TLegend *leg = new TLegend(0.2,0.2,0.3,0.25);
      leg->SetBorderSize(0);
      leg->SetTextFont(62);
      leg->SetTextSize(0.035);
      leg->SetLineColor(1);
      leg->SetLineStyle(1);
      leg->SetLineWidth(1);
      leg->SetFillColor(0);
      leg->SetFillStyle(1001);
      leg->AddEntry(h_SF_new,legend[n],"");
      TCanvas *c2 = new TCanvas("c2", "SF");
      c2->cd();
      h_SF_new->Draw();
      leg->Draw();
      TLatex T6; T6.SetTextFont(42); T6.SetTextSize(0.04875); T6.SetTextAlign(31); T6.SetLineWidth(2); T6.SetNDC();
      T6.DrawLatex(0.98,0.95125,"#sqrt{s} = 13 TeV, L = 2460 pb^{-1}, 25 ns");
      c2->Print("SF_"+wp[n]+".eps");

      //CALCULATION OF THE SYSTEMATIC ERROR
      
      double_t err_DY = 0.;
      double_t err_ST = 0.;
      double_t err_WJets = 0.;
      double_t err_QCD = 0.;
      double_t system_uncer = 0.;
		       
      for(unsigned int m = 0; m < files_mc.size(); m++)
	{
	  TFile *file= new TFile(files_mc[m]);
	  file->cd();
	  if (m == 1 || m == 2) 
	    { 
	      if (m == 1){
		gDirectory->GetObject("AfterCuts_1/PTTop",h_DY_50_2 );
		gDirectory->GetObject(wp_2[n]+"/PTTop",h_DY_50_3 );
	      }
	      if (m == 2){
		TH1F *h_tmp_2; gDirectory->GetObject("AfterCuts_1/PTTop",h_DY_50_2 );
		TH1F *h_tmp_3; gDirectory->GetObject(wp_2[n]+"/PTTop",h_DY_50_3 );
		h_mc_2->Add(h_DY_50_2);
		h_mc_3->Add(h_DY_50_3);
		h_DY_50_2->Scale(0.5);
		h_DY_50_3->Scale(0.5);
	      }
   
	    }
	  if (m == 3 || m == 4 || m == 5) 
	    { 
	      if (m == 3){
		gDirectory->GetObject("AfterCuts_1/PTTop",h_ST_50_2 );
		gDirectory->GetObject(wp_2[n]+"/PTTop",h_ST_50_3 );
	      }
	      if (m == 4 || m == 5){
		TH1F *h_tmp_2; gDirectory->GetObject("AfterCuts_1/PTTop",h_tmp_2 );
		TH1F *h_tmp_3; gDirectory->GetObject(wp_2[n]+"/PTTop",h_tmp_3 );
		h_mc_2->Add(h_ST_50_2);
		h_mc_3->Add(h_ST_50_3);
		if (m == 5) {
		  h_ST_50_2->Scale(0.5);
		  h_ST_50_3->Scale(0.5);
		}
	      }
	    }
	  if (m == 6) 
	    { 
		gDirectory->GetObject("AfterCuts_1/PTTop",h_WJets_50_2 );
		gDirectory->GetObject(wp_2[n]+"/PTTop",h_WJets_50_3 );
		h_WJets_50_2->Scale(0.5);
		h_WJets_50_3->Scale(0.5);
	    }
	  if (m == 7) 
	    { 
		gDirectory->GetObject("AfterCuts_1/PTTop",h_QCD_50_2 );
		gDirectory->GetObject(wp_2[n]+"/PTTop",h_QCD_50_3 );
		h_WJets_50_2->Scale(0.5);
		h_WJets_50_3->Scale(0.5);
	    }
	 
	}
      TH1F *h_data_2_err_DY = (TH1F*)h_data_2->Clone("h_data_2_err_DY");
      TH1F *h_data_3_err_DY = (TH1F*)h_data_3->Clone("h_data_3_err_DY");
      h_data_2_err_DY->Add(h_DY_50_2, 1);
      h_data_3_err_DY->Add(h_DY_50_3, 1);
      TH1F *h_data_2_err_ST = (TH1F*)h_data_2->Clone("h_data_2_err_ST");
      TH1F *h_data_3_err_ST = (TH1F*)h_data_3->Clone("h_data_3_err_ST");
      h_data_2_err_ST->Add(h_ST_50_2, 1);
      h_data_3_err_ST->Add(h_ST_50_3, 1);
      TH1F *h_data_2_err_WJets = (TH1F*)h_data_2->Clone("h_data_2_err_WJets");
      TH1F *h_data_3_err_WJets = (TH1F*)h_data_3->Clone("h_data_3_err_WJets");
      h_data_2_err_WJets->Add(h_WJets_50_2, 1);
      h_data_3_err_WJets->Add(h_WJets_50_3, 1);
      TH1F *h_data_2_err_QCD = (TH1F*)h_data_2->Clone("h_data_2_err_QCD");
      TH1F *h_data_3_err_QCD = (TH1F*)h_data_3->Clone("h_data_3_err_QCD");
      h_data_2_err_QCD->Add(h_QCD_50_2, 1);
      h_data_3_err_QCD->Add(h_QCD_50_3, 1);

      h_data_2_new_err = h_data_2_err_DY->Rebin(1,"h_data_2_new_err_DY",xbins2);
      h_data_3_new_err = h_data_3_err_DY->Rebin(1,"h_data_3_new_err_DY",xbins2);
      h_data_eff_new_err = h_data_eff->Rebin(1,"h_data_eff_new_err",xbins2);
      h_SF_new_err_DY = h_SF->Rebin(1,"h_SF_new_err_DY",xbins2);
      h_data_eff_new_err->Divide(h_data_3_new_err,h_data_2_new_err,1,1,"b");
      h_SF_new_err_DY->Divide(h_data_eff_new_err, h_mc_eff_new2,1,1,"");

      h_data_2_new_err->Reset();
      h_data_3_new_err->Reset();
      h_data_eff_new_err->Reset();
      h_data_2_new_err = h_data_2_err_ST->Rebin(1,"h_data_2_new_err_ST",xbins2);
      h_data_3_new_err = h_data_3_err_ST->Rebin(1,"h_data_3_new_err_ST",xbins2);
      h_SF_new_err_ST= h_SF->Rebin(1,"h_SF_new_err_ST",xbins2);
      h_data_eff_new_err->Divide(h_data_3_new_err,h_data_2_new_err,1,1,"b");
      h_SF_new_err_ST->Divide(h_data_eff_new_err, h_mc_eff_new2,1,1,"");

      h_data_2_new_err->Reset();
      h_data_3_new_err->Reset();
      h_data_eff_new_err->Reset();
      h_data_2_new_err = h_data_2_err_WJets->Rebin(1,"h_data_2_new_err_WJets",xbins2);
      h_data_3_new_err = h_data_3_err_WJets->Rebin(1,"h_data_3_new_err_WJets",xbins2);
      h_SF_new_err_WJets= h_SF->Rebin(1,"h_SF_new_err_WJets",xbins2);
      h_data_eff_new_err->Divide(h_data_3_new_err,h_data_2_new_err,1,1,"b");
      h_SF_new_err_WJets->Divide(h_data_eff_new_err, h_mc_eff_new2,1,1,"");

      h_data_2_new_err->Reset();
      h_data_3_new_err->Reset();
      h_data_eff_new_err->Reset();
      h_data_2_new_err = h_data_2_err_QCD->Rebin(1,"h_data_2_new_err_QCD",xbins2);
      h_data_3_new_err = h_data_3_err_QCD->Rebin(1,"h_data_3_new_err_QCD",xbins2);
      h_SF_new_err_QCD= h_SF->Rebin(1,"h_SF_new_err_QCD",xbins2);
      h_data_eff_new_err->Divide(h_data_3_new_err,h_data_2_new_err,1,1,"b");
      h_SF_new_err_QCD->Divide(h_data_eff_new_err, h_mc_eff_new2,1,1,"");

      system_uncer = sqrt(TMath::Power(h_SF_new2->Integral() - h_SF_new_err_DY->Integral(), 2)+TMath::Power(h_SF_new2->Integral() - h_SF_new_err_ST->Integral(), 2)+TMath::Power(h_SF_new2->Integral() - h_SF_new_err_WJets->Integral(), 2)+TMath::Power(h_SF_new2->Integral() - h_SF_new_err_QCD->Integral(), 2));
      
      std::cout << system_uncer << std::endl;

      output << legend[n] << "; " << h_SF_new->GetBinContent(2) << "; " << h_SF_new->GetBinError(2) << "; " <<  h_SF_new->GetBinContent(3) << "; " << h_SF_new->GetBinError(3)<< "; " << h_SF_new2->GetBinContent(1) << "; " << h_SF_new2->GetBinError(1) <<std::endl;

      
 
   
    }
}
