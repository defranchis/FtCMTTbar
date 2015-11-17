vector<TString> Files_MC(vector<TString> list)
{
  list.push_back("uhh2.AnalysisModuleRunner.MC.TTbar.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-10to50.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_t-channel.root"); 
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_tW_antitop.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.ST_tW_top.root");
  list.push_back("uhh2.AnalysisModuleRunner.MC.WJets.root");
  return list;
}

vector<TString> Selection_steps(vector<TString> list)
{
  list.push_back("NoCuts");
  list.push_back("AfterCuts_1");
  list.push_back("AfterCuts_2");
  list.push_back("AfterCuts_3"); 
  list.push_back("AfterCuts_4");
  list.push_back("AfterCuts");
  return list;
}

vector<TString> Names(vector<TString> list)
{
  list.push_back("ttbar");
  list.push_back("DY+Jets");
  list.push_back("DY+Jets");
  list.push_back("Single Top"); 
  list.push_back("Single Top");
  list.push_back("Single Top");
  list.push_back("W+Jets");
  return list;
}

vector<TString> Hists(vector<TString> list)
{
  list.push_back("MassTop");
  list.push_back("PTTop");
  list.push_back("PrimaryVertex");
  //list.push_back("subSecondaryVertex");
  //list.push_back("subTrackMomentum");
  list.push_back("MassTop_sub");
  list.push_back("m12");
  list.push_back("m13");
  list.push_back("m23");
  list.push_back("fRec");
  list.push_back("HTTmass");
  list.push_back("tau21");
  list.push_back("tau32");
  //list.push_back("wmass");
  list.push_back("neutralEmEnergyFraction");
  list.push_back("neutralHadronEnergyFraction");
  list.push_back("neutralMultiplicity");
  return list;
}
vector<TString> StackHists(vector<TString> list)
{
  list.push_back("TopMass");
  list.push_back("TopPT");
  list.push_back("PV");
  //list.push_back("SV");
  //list.push_back("SJ_PT");
  list.push_back("TopMass_sub");
  list.push_back("M12");
  list.push_back("M13");
  list.push_back("M23");
  list.push_back("FREC");
  list.push_back("HTTMASS");
  list.push_back("TAU21");
  list.push_back("TAU32");
  //list.push_back("WMASS");
  list.push_back("NeutralEmEnergyFraction");
  list.push_back("NeutralHadronEnergyFraction");
  list.push_back("NeutralMultiplicity");
  return list;
}
vector<TString> Description(vector<TString> list)
{
  list.push_back("Top Mass  v4().M()");
  list.push_back("Top PT");
  list.push_back("Primary Vertex");
  //list.push_back("Secondary Vertex");
  //list.push_back("Subjet Track PT");
  list.push_back("Top Mass (sum of subjets)");
  list.push_back("mass of first and second subjet");
  list.push_back("mass of first and third subjet");
  list.push_back("mass of second and third subjet");
  list.push_back("fRec");
  list.push_back("HTTmass");
  list.push_back("tau21");
  list.push_back("tau32");
  //list.push_back("wmass");
  list.push_back("Neutral Em Energy Fraction");
  list.push_back("Neutral Hadron Energy Fraction");
  list.push_back("Neutral Multiplicity");
  return list;
}
vector<TString> Flavour(vector<TString> list)
{
  list.push_back("b");
  list.push_back("c");
  list.push_back("uds");
  list.push_back("g");
  list.push_back("none");
  return list;
}
vector<TString> YAxis(vector<TString> list)
{
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of vertices");
  //list.push_back("number of vertices");
  //list.push_back("number of tracks");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  //list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  list.push_back("number of topjets");
  return list;
}
vector<TString> XAxis(vector<TString> list)
{
  list.push_back("m_{top} [GeV]");
  list.push_back("PT_{top} [GeV]");
  list.push_back("multiplicity");
  //list.push_back("inv. mass [GeV]");
  //list.push_back("PT_{track} [GeV]");
  list.push_back("m_{top} [GeV]");
  list.push_back("m_{12} [GeV]");
  list.push_back("m_{13} [GeV]");
  list.push_back("m_{23} [GeV]");
  list.push_back("fRec");
  list.push_back("HTTmass [GeV]");
  list.push_back("tau21");
  list.push_back("tau32");
  //list.push_back("m_{W} [GeV]");
  list.push_back("Neutral Em Energy Fraction");
  list.push_back("Neutral Hadron Energy Fraction");
  list.push_back("Neutral Multiplicity");
  return list;
}

void NumberofEvents_plot()
{
  TString selectionlevel = "AfterCuts";

  vector<TString> files_mc, selection_steps, names, hists, stackhists, description, xaxis, yaxis, flavour;
  files_mc=Files_MC(files_mc);
  hists=Hists(hists);
  selection_steps=Selection_steps(selection_steps);
  names=Names(names);
  stackhists=StackHists(stackhists);
  description=Description(description);
  flavour=Flavour(flavour);
  xaxis=XAxis(xaxis);
  yaxis=YAxis(yaxis);
  
  TFile * ofile = TFile::Open("NumberofEvents.root","RECREATE");
  ofile->cd();

  //  THStack *h_NoE = new THStack("NoE","Number of Events at different selection levels");

  TLegend *leg = new TLegend(0.60,0.65,0.955,0.9);
  leg->SetBorderSize(0);
  leg->SetTextFont(62);
  leg->SetTextSize(0.05);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
  
  /*for(int m = 0; m < files_mc.size(); m++)
    {
      TFile *file=TFile::Open(files_mc[m]);
      std::cout << files_mc[m] << std::endl;
      TH1F *h_level= new TH1F("Level0", "Level 0",6,0.,6.);

      for(int n = 0; n < selection_steps.size(); n++)
	{
	  TH1F *h; gDirectory->GetObject(selection_steps[n]+"/NumberofEvents",h);
	  Double_t NoE = h->GetBinContent(2);
	  std::cout << NoE << std::endl;
	  if(n==0) h_level->Fill(0., NoE); 
	  if(n==1) h_level->Fill(1., NoE); 
	  if(n==2) h_level->Fill(2., NoE); 
	  if(n==3) h_level->Fill(3., NoE); 
	  if(n==4) h_level->Fill(4., NoE); 
	  if(n==5) h_level->Fill(5., NoE); 
	}

      h_level->SetFillColor(m+2); 
      h_NoE->Add(h_level);
      if(m == 0 || m == 2 || m == 3 || m == 6) leg->AddEntry(h_level,names[m],"f");
    }
  TFile *file_data=TFile::Open("uhh2.AnalysisModuleRunner.DATA.Data.root");
  TH1F *h_level_data= new TH1F("LevelData", "Number of Events at different selection levels",6,0.,6.);
    
  for(int n = 0; n < selection_steps.size(); n++)
    {
      TH1F *h; gDirectory->GetObject(selection_steps[n]+"/NumberofEvents",h);
      Double_t NoE = h->GetBinContent(2);
      std::cout << NoE << std::endl;
      if(n==0) h_level_data->Fill(0., NoE); 
      if(n==1) h_level_data->Fill(1., NoE); 
      if(n==2) h_level_data->Fill(2., NoE); 
      if(n==3) h_level_data->Fill(3., NoE); 
      if(n==4) h_level_data->Fill(4., NoE); 
      if(n==5) h_level_data->Fill(5., NoE); 	    
      }*/
    
  gStyle->SetOptStat("");
  gStyle->SetLabelFont(42);
  gStyle->SetLabelSize(0.035, "X");
  gStyle->SetLabelSize(0.05, "Y");
  gStyle->SetTitleSize(0.035, "X");
  gStyle->SetTitleSize(0.06, "Y");
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
  TLatex T1; T1.SetTextFont(61); T1.SetTextSize(0.07475); T1.SetTextAlign(11); T1.SetLineWidth(2); T1.SetNDC();
  TLatex T2; T2.SetTextFont(52); T2.SetTextSize(0.05681); T2.SetTextAlign(13); T2.SetLineWidth(2); T2.SetNDC();
  TLatex T3; T3.SetTextFont(42); T3.SetTextSize(0.05681); T3.SetTextAlign(12); T3.SetLineWidth(2); T3.SetNDC();
  TLatex T4; T4.SetTextFont(42); T4.SetTextSize(0.05681); T4.SetTextAlign(12); T4.SetLineWidth(2); T4.SetNDC();
  TLatex T5; T5.SetTextFont(42); T5.SetTextSize(0.05681); T5.SetTextAlign(12); T5.SetLineWidth(2); T5.SetNDC();
  TLatex T6; T6.SetTextFont(42); T6.SetTextSize(0.04875); T6.SetTextAlign(31); T6.SetLineWidth(2); T6.SetNDC();

  /*TCanvas *c1 = new TCanvas("c1", "Selection steps");
  c1->cd();
  h_level_data->SetXTitle("selection level");
  h_level_data->SetYTitle("number of events");
  h_level_data->Draw("P");
  for(int i = 0; i<6; i++)
    {
      h_level_data->GetXaxis()->SetBinLabel(i+1,selection_steps[i]);
    }

  h_level_data->Sumw2();
  h_level_data->SetMarkerStyle(20);
  h_level_data->SetMarkerSize(1); 
  h_NoE->Draw("same""hist");
  h_level_data->Draw("P""same");
  leg->AddEntry(h_level_data,"data","p");
  leg->Draw();
  c1->Print("Plots_2.pdf[");
  c1->Print("Plots_2.pdf");
  
  */

  for(int k = 0; k < hists.size(); k++)
    {
 
      THStack *h_stack = new THStack("stack", description[k]);

      TLegend *leg = new TLegend(0.60,0.65,0.955,0.9);
      leg->SetBorderSize(0);
      leg->SetTextFont(62);
      leg->SetTextSize(0.05);
      leg->SetLineColor(1);
      leg->SetLineStyle(1);
      leg->SetLineWidth(1);
      leg->SetFillColor(0);
      leg->SetFillStyle(1001);
      
      for(int m = 0; m < files_mc.size(); m++)
	{
	  TFile *file= new TFile(files_mc[m]);
	  std::cout << selectionlevel+"/"+hists[k] << std::endl;
	  file->cd();
	  
	  TH1F *h_tmphist; 
	  if(k == 3 || k == 4)
	    {
	      gDirectory->GetObject(selectionlevel+"/"+hists[k]+"_b",h_tmphist);
	      for(int l = 1; l < flavour.size(); l++)
		{
		  TH1F *h_tmphistflavour; gDirectory->GetObject(selectionlevel+"/"+hists[k]+"_"+flavour[l],h_tmphistflavour);
		  h_tmphist->Add(h_tmphistflavour);
		}
	    }
	  else
	    {
	      gDirectory->GetObject(selectionlevel+"/"+hists[k],h_tmphist);
	    }
	  
	  if (m == 0 || m == 6)
	    {
	      h_tmphist->SetFillColor(m+2); h_tmphist->SetLineColor(m+2);
	    }
	  std::cout << "Test1" << k << std::endl;
	  if (m == 1 || m == 2)
	    {
	      h_tmphist->SetFillColor(4); h_tmphist->SetLineColor(4);
	     
	    }
	  std::cout << "Test2" << k << std::endl;
	  if (m == 3 || m == 4 || m == 5)
	    {
	      h_tmphist->SetFillColor(5); h_tmphist->SetLineColor(5);
	    }
	  h_stack->Add(h_tmphist); 
	  if(m == 0 || m == 2 || m == 3 || m == 6) leg->AddEntry(h_tmphist,names[m],"f");
	}
      std::cout << "MC End" << std::endl;
      TFile *file_data=TFile::Open("uhh2.AnalysisModuleRunner.DATA.Data.root");
      TH1F *h_tmphist_data; 
      if(k == 3 || k == 4)
	{
	  gDirectory->GetObject(selectionlevel+"/"+hists[k]+"_none",h_tmphist_data);
	}
      else
	{
	  gDirectory->GetObject(selectionlevel+"/"+hists[k],h_tmphist_data);
	}
      TCanvas *c2 = new TCanvas("c2", "Top Mass");
      c2->cd();
      double_t yrange=h_tmphist_data->GetMaximum();
      h_tmphist_data->SetMaximum(2*yrange);
      h_tmphist_data->SetXTitle(xaxis[k]);
      h_tmphist_data->SetYTitle(yaxis[k]);
      h_tmphist_data->SetTitle(description[k]);
      h_tmphist_data->Sumw2();
      h_tmphist_data->SetMarkerStyle(20);
      h_tmphist_data->SetMarkerSize(1);
      h_tmphist_data->Draw("P");
      h_stack->Draw("hist""same");
      h_tmphist_data->Draw("P""same");
      leg->Draw();
      T6.DrawLatex(0.98,0.95125,"#sqrt{s} = 13 TeV, 25 ns");
      c2->Print(hists[k]+".png");
      c2->Print("Plots_2.pdf");
      if(k == stackhists.size()-1)
	{
	  c2->Print("Plots_2.pdf]");
	}
      
    }

  // T1.DrawLatex(0.1969,0.906825, "CMS");
  // T2.DrawLatex(0.1969,0.817125,"Preliminary");
  // T3.DrawLatex(0.1969,0.727425, "t#bar{t} sample");
  // T4.DrawLatex(0.1969,0.668725, "HepTopTagger subjets");
  // T5.DrawLatex(0.1969,0.603725, "CA15 jets, p_{T} > 150 GeV");
  // T6.DrawLatex(0.98,0.95125,"#sqrt{s} = 13 TeV, 50 ns");
  ofile->Close();
}


// void NumberofEvents_plot()
// {
//   TString selectionlevel = "AfterCuts_2/";

//   vector<TString> files_mc, selection_steps, names, hists, stackhists, description;
//   files_mc=Files_MC(files_mc);
//   hists=Hists(hists);
//   selection_steps=Selection_steps(selection_steps);
//   names=Names(names);
//   stackhists=StackHists(stackhists);
//   description=Description(description);

//   THStack *h_NoE = new THStack("NoE","Number of Events at different selection levels");
//   THStack *h_TopMass = new THStack("TopMass","Top Mass");
//   THStack *h_TopPT = new THStack("TopMass","Top PT");
//   THStack *h_PV = new THStack("PV","Primary Vertex");
//   THStack *h_SV = new THStack("SV","Secondary Vertex");
//   THStack *h_SJ_PT = new THStack("SJ_PT","Subjet Track PT");
//   THStack *h_TopMass_sub = new THStack("TopMass","Top Mass from subjets");
//   THStack *h_M12 = new THStack("M12","mass of first and second subjet");
//   THStack *h_M13 = new THStack("M13","mass of first and third subjet");
//   THStack *h_M23 = new THStack("M23","mass of second and third subjet");
//   THStack *h_FREC = new THStack("FREC","fRec");
//   THStack *h_HTTMASS = new THStack("FREC","HTTmass");
//   THStack *h_TAU21 = new THStack("TAU21","tau21");
//   THStack *h_TAU32 = new THStack("TAU32","tau32");
//   THStack *h_WMASS = new THStack("WMASS","wmass");

 
//   TFile * ofile = TFile::Open("NumberofEvents.root","RECREATE");
//   ofile->cd();

//   TLegend *leg = new TLegend(0.60,0.65,0.955,0.9);
//   leg->SetBorderSize(0);
//   leg->SetTextFont(62);
//   leg->SetTextSize(0.05);
//   leg->SetLineColor(1);
//   leg->SetLineStyle(1);
//   leg->SetLineWidth(1);
//   leg->SetFillColor(0);
//   leg->SetFillStyle(1001);

//   for(int m = 0; m < files_mc.size(); m++)
//     //for(int m = 0; m < 1; m++)
//     {
      
//       TFile *file=TFile::Open(files_mc[m]);
//       std::cout << files_mc[m] << std::endl;
//       TH1F *h_tm; gDirectory->GetObject(selectionlevel+"MassTop",h_tm);
//       TH1F *h_tpt; gDirectory->GetObject(selectionlevel+"PTTop",h_tpt);
//       TH1F *h_pv; gDirectory->GetObject(selectionlevel+"PrimaryVertex",h_pv);
//       TH1F *h_sv_b; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_b",h_sv_b);
//       TH1F *h_sv_c; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_c",h_sv_c);
//       TH1F *h_sv_uds; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_uds",h_sv_uds);
//       TH1F *h_sv_g; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_g",h_sv_g);
//       TH1F *h_sv_none; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_none",h_sv_none);
//       TH1F *h_sjpt_b; gDirectory->GetObject(selectionlevel+"subTrackMomentum_b",h_sjpt_b);
//       TH1F *h_sjpt_c; gDirectory->GetObject(selectionlevel+"subTrackMomentum_c",h_sjpt_c);
//       TH1F *h_sjpt_uds; gDirectory->GetObject(selectionlevel+"subTrackMomentum_uds",h_sjpt_uds);
//       TH1F *h_sjpt_g; gDirectory->GetObject(selectionlevel+"subTrackMomentum_g",h_sjpt_g);
//       TH1F *h_sjpt_none; gDirectory->GetObject(selectionlevel+"subTrackMomentum_none",h_sjpt_none);
//       TH1F *h_tm_sub; gDirectory->GetObject(selectionlevel+"MassTop_sub",h_tm_sub);
//       TH1F *h_m12; gDirectory->GetObject(selectionlevel+"m12",h_m12);
//       TH1F *h_m13; gDirectory->GetObject(selectionlevel+"m13",h_m13);
//       TH1F *h_m23; gDirectory->GetObject(selectionlevel+"m23",h_m23);
//       TH1F *h_fRec; gDirectory->GetObject(selectionlevel+"fRec",h_fRec);
//       TH1F *h_HTTmass; gDirectory->GetObject(selectionlevel+"HTTmass",h_HTTmass);
//       TH1F *h_tau21; gDirectory->GetObject(selectionlevel+"tau21",h_tau21);
//       TH1F *h_tau32; gDirectory->GetObject(selectionlevel+"tau32",h_tau32);
//       TH1F *h_wmass; gDirectory->GetObject(selectionlevel+"wmass",h_wmass);

//       h_sv_b->Add(h_sv_c);
//       h_sv_b->Add(h_sv_uds);
//       h_sv_b->Add(h_sv_g);
//       h_sv_b->Add(h_sv_none);
//       h_sjpt_b->Add(h_sjpt_c);
//       h_sjpt_b->Add(h_sjpt_uds);
//       h_sjpt_b->Add(h_sjpt_g);
//       h_sjpt_b->Add(h_sjpt_none);
  
      
//       if (m == 0 || m == 6)
// 	{
//       h_tm->SetFillColor(m+2); h_tm->SetLineColor(m+2);
//       h_tpt->SetFillColor(m+2); h_tpt->SetLineColor(m+2);
//       h_pv->SetFillColor(m+2); h_pv->SetLineColor(m+2);
//       h_sv_b->SetFillColor(m+2); h_sv_b->SetLineColor(m+2);
//       h_sjpt_b->SetFillColor(m+2); h_sjpt_b->SetLineColor(m+2);
//       h_tm_sub->SetFillColor(m+2); h_tm_sub->SetLineColor(m+2);
//       h_m12->SetFillColor(m+2); h_m12->SetLineColor(m+2);
//       h_m13->SetFillColor(m+2); h_m13->SetLineColor(m+2);
//       h_m23->SetFillColor(m+2); h_m23->SetLineColor(m+2);
//       h_HTTmass->SetFillColor(m+2); h_HTTmass->SetLineColor(m+2);
//       h_fRec->SetFillColor(m+2); h_fRec->SetLineColor(m+2);
//       h_tau21->SetFillColor(m+2); h_tau21->SetLineColor(m+2);
//       h_tau32->SetFillColor(m+2); h_tau32->SetLineColor(m+2);
//       h_wmass->SetFillColor(m+2); h_wmass->SetLineColor(m+2);
// 	}
//       if (m == 1 || m == 2)
// 	{
// 	  h_tm->SetFillColor(4); h_tm->SetLineColor(4);
// 	  h_tpt->SetFillColor(4); h_tpt->SetLineColor(4); 
// 	  h_pv->SetFillColor(4);  h_pv->SetLineColor(4);
// 	  h_sv_b->SetFillColor(4);  h_sv_b->SetLineColor(4);
// 	  h_sjpt_b->SetFillColor(4);  h_sjpt_b->SetLineColor(4);
// 	  h_tm_sub->SetFillColor(4); h_tm_sub->SetLineColor(4);
// 	  h_m12->SetFillColor(4); h_m12->SetLineColor(4);
// 	  h_m13->SetFillColor(4); h_m13->SetLineColor(4);
// 	  h_m23->SetFillColor(4); h_m23->SetLineColor(4);
// 	  h_HTTmass->SetFillColor(4); h_HTTmass->SetLineColor(4);
// 	  h_fRec->SetFillColor(4); h_fRec->SetLineColor(4);
// 	  h_tau21->SetFillColor(4); h_tau21->SetLineColor(4);
// 	  h_tau32->SetFillColor(4); h_tau32->SetLineColor(4);
// 	  h_wmass->SetFillColor(4); h_wmass->SetLineColor(4);
// 	}
//       if (m == 3 || m == 4 || m == 5)
// 	{
// 	  h_tm->SetFillColor(5); h_tm->SetLineColor(5);
// 	  h_tpt->SetFillColor(5); h_tpt->SetLineColor(5);
// 	  h_pv->SetFillColor(5); h_pv->SetLineColor(5);
// 	  h_sv_b->SetFillColor(5); h_sv_b->SetLineColor(5);
// 	  h_sjpt_b->SetFillColor(5); h_sjpt_b->SetLineColor(5);
// 	  h_tm_sub->SetFillColor(5); h_tm_sub->SetLineColor(5);
// 	  h_m12->SetFillColor(5); h_m12->SetLineColor(5);
// 	  h_m13->SetFillColor(5); h_m13->SetLineColor(5);
// 	  h_m23->SetFillColor(5); h_m23->SetLineColor(5);
// 	  h_HTTmass->SetFillColor(5); h_HTTmass->SetLineColor(5);
// 	  h_fRec->SetFillColor(5); h_fRec->SetLineColor(5);
// 	  h_tau21->SetFillColor(5); h_tau21->SetLineColor(5);
// 	  h_tau32->SetFillColor(5); h_tau32->SetLineColor(5);
// 	  h_wmass->SetFillColor(5); h_wmass->SetLineColor(5);
// 	}
//       h_TopMass->Add(h_tm);
//       h_TopPT->Add(h_tpt);
//       h_PV->Add(h_pv);
//       h_SV->Add(h_sv_b);
//       h_SJ_PT ->Add(h_sjpt_b);
//       h_TopMass_sub->Add(h_tm_sub);
//       h_M12->Add(h_m12);
//       h_M13->Add(h_m13);
//       h_M23->Add(h_m23);
//       h_FREC->Add(h_fRec);
//       h_HTTMASS->Add(h_HTTmass);
//       h_TAU21->Add(h_tau21);
//       h_TAU32->Add(h_tau32);
//       h_WMASS->Add(h_wmass);
      
//       TH1F *h_level= new TH1F("Level0", "Level 0",6,0.,6.);

//       for(int n = 0; n < selection_steps.size(); n++)
// 	{
// 	  TH1F *h; gDirectory->GetObject(selection_steps[n]+"/NumberofEvents",h);
// 	  Double_t NoE = h->GetBinContent(2);
// 	  std::cout << NoE << std::endl;
// 	  if(n==0) h_level->Fill(0., NoE); 
// 	  if(n==1) h_level->Fill(1., NoE); 
// 	  if(n==2) h_level->Fill(2., NoE); 
// 	  if(n==3) h_level->Fill(3., NoE); 
// 	  if(n==4) h_level->Fill(4., NoE); 
// 	  if(n==5) h_level->Fill(5., NoE); 
	    
// 	}

//       h_level->SetFillColor(m+2); 
//       h_NoE->Add(h_level);
//       if(m == 0 || m == 2 || m == 3 || m == 6) leg->AddEntry(h_level,names[m],"f");

//     }

//   TFile *file_data=TFile::Open("uhh2.AnalysisModuleRunner.DATA.Data.root");
//   TH1F *h_level_data= new TH1F("LevelData", "Number of Events at different selection levels",6,0.,6.);
//   TH1F *h_tm_data; gDirectory->GetObject(selectionlevel+"MassTop",h_tm_data);
//   TH1F *h_tm_sub_data; gDirectory->GetObject(selectionlevel+"MassTop_sub",h_tm_sub_data);
//   TH1F *h_tpt_data; gDirectory->GetObject(selectionlevel+"PTTop",h_tpt_data);
//   TH1F *h_pv_data; gDirectory->GetObject(selectionlevel+"PrimaryVertex",h_pv_data);
//   TH1F *h_sv_data; gDirectory->GetObject(selectionlevel+"subSecondaryVertex_none",h_sv_data);
//   TH1F *h_sjpt_data; gDirectory->GetObject(selectionlevel+"subTrackMomentum_none",h_sjpt_data);
//   TH1F *h_m12_data; gDirectory->GetObject(selectionlevel+"m12",h_m12_data);
//   TH1F *h_m13_data; gDirectory->GetObject(selectionlevel+"m13",h_m13_data);
//   TH1F *h_m23_data; gDirectory->GetObject(selectionlevel+"m23",h_m23_data);
//   TH1F *h_fRec_data; gDirectory->GetObject(selectionlevel+"fRec",h_fRec_data);
//   TH1F *h_HTTmass_data; gDirectory->GetObject(selectionlevel+"HTTmass",h_HTTmass_data);
//   TH1F *h_tau21_data; gDirectory->GetObject(selectionlevel+"tau21",h_tau21_data);
//   TH1F *h_tau32_data; gDirectory->GetObject(selectionlevel+"tau32",h_tau32_data);
//   TH1F *h_wmass_data; gDirectory->GetObject(selectionlevel+"wmass",h_wmass_data);

//   for(int n = 0; n < selection_steps.size(); n++)
//     {
//       TH1F *h; gDirectory->GetObject(selection_steps[n]+"/NumberofEvents",h);
//       Double_t NoE = h->GetBinContent(2);
//       std::cout << NoE << std::endl;
//       if(n==0) h_level_data->Fill(0., NoE); 
//       if(n==1) h_level_data->Fill(1., NoE); 
//       if(n==2) h_level_data->Fill(2., NoE); 
//       if(n==3) h_level_data->Fill(3., NoE); 
//       if(n==4) h_level_data->Fill(4., NoE); 
//       if(n==5) h_level_data->Fill(5., NoE); 	    
//     }
 
//   gStyle->SetOptStat("");
//   gStyle->SetLabelFont(42);
//   gStyle->SetLabelSize(0.035, "X");
//   gStyle->SetLabelSize(0.05, "Y");
//   gStyle->SetTitleSize(0.035, "X");
//   gStyle->SetTitleSize(0.06, "Y");
//   gStyle->SetTitleFont(42);
//   gStyle->SetPadBorderMode(0);
//   gStyle->SetPadBorderSize(2);
//   gStyle->SetPadTickX(1);
//   gStyle->SetPadTickY(1);
//   gStyle->SetPadLeftMargin(0.16);
//   gStyle->SetPadRightMargin(0.02);
//   gStyle->SetPadTopMargin(0.065);
//   gStyle->SetPadBottomMargin(0.13);
//   gStyle->SetOptStat("");
//   TLatex T1; T1.SetTextFont(61); T1.SetTextSize(0.07475); T1.SetTextAlign(11); T1.SetLineWidth(2); T1.SetNDC();
//   TLatex T2; T2.SetTextFont(52); T2.SetTextSize(0.05681); T2.SetTextAlign(13); T2.SetLineWidth(2); T2.SetNDC();
//   TLatex T3; T3.SetTextFont(42); T3.SetTextSize(0.05681); T3.SetTextAlign(12); T3.SetLineWidth(2); T3.SetNDC();
//   TLatex T4; T4.SetTextFont(42); T4.SetTextSize(0.05681); T4.SetTextAlign(12); T4.SetLineWidth(2); T4.SetNDC();
//   TLatex T5; T5.SetTextFont(42); T5.SetTextSize(0.05681); T5.SetTextAlign(12); T5.SetLineWidth(2); T5.SetNDC();
//   TLatex T6; T6.SetTextFont(42); T6.SetTextSize(0.04875); T6.SetTextAlign(31); T6.SetLineWidth(2); T6.SetNDC();

//   TCanvas *c1 = new TCanvas("c1", "Best Significance MHT vs. squarkmass");
//   c1->cd();
//   h_level_data->SetXTitle("selection level");
//   h_level_data->SetYTitle("number of events");
//   h_level_data->Draw("P");
//   for(int i = 0; i<6; i++)
//     {
//       h_level_data->GetXaxis()->SetBinLabel(i+1,selection_steps[i]);
//     }


//   h_level_data->Sumw2();
//   h_level_data->SetMarkerStyle(20);
//   h_level_data->SetMarkerSize(1); 
//   h_NoE->Draw("same""hist");
//   h_level_data->Draw("P""same");
//   leg->AddEntry(h_level_data,"data","p");
//   leg->Draw();
//   c1->Print("Plots_2.pdf[");
//   c1->Print("Plots_2.pdf");
//   c1->Print("Plots_2.pdf");

//   TCanvas *c2 = new TCanvas("c2", "Top Mass");
//   c2->cd();
//   double_t yrange=h_tm_data->GetMaximum();
//   h_tm_data->SetMaximum(2*yrange);
//   h_tm_data->SetXTitle("m_{top} [GeV]");
//   h_tm_data->SetYTitle("number of topjets");
//   h_tm_data->Sumw2();
//   h_tm_data->SetMarkerStyle(20);
//   h_tm_data->SetMarkerSize(1);
//   h_tm_data->Draw("P");
//   h_TopMass->Draw("hist""same");
//   h_tm_data->Draw("P""same");
//   leg->Draw();

//   // T1.DrawLatex(0.1969,0.906825, "CMS");
//   // T2.DrawLatex(0.1969,0.817125,"Preliminary");
//   // T3.DrawLatex(0.1969,0.727425, "t#bar{t} sample");
//   // T4.DrawLatex(0.1969,0.668725, "HepTopTagger subjets");
//   // T5.DrawLatex(0.1969,0.603725, "CA15 jets, p_{T} > 150 GeV");
//   // T6.DrawLatex(0.98,0.95125,"#sqrt{s} = 13 TeV, 50 ns");
//   c2->Print("Topmass.png");
//   c2->Print("Plots_2.pdf");

//   TCanvas *c3 = new TCanvas("c3", "Top PT");
  
//   c3->cd();
//   yrange=h_tpt_data->GetMaximum();
//   h_tpt_data->SetMaximum(2*yrange);
//   h_tpt_data->SetXTitle("PT_{top} [GeV]");
//   h_tpt_data->SetYTitle("");
//   h_tpt_data->Sumw2();
//   h_tpt_data->SetMarkerStyle(20);
//   h_tpt_data->SetMarkerSize(1);
//   h_tpt_data->Draw("P");
//   h_TopPT->Draw("hist""same");
//   h_tpt_data->Draw("P""same");
//   leg->Draw();
//   c3->Print("toppt.png");
//   c3->Print("Plots_2.pdf");

//   TCanvas *c4 = new TCanvas("c4", "Primary Vertex");
  
//   c4->cd();
//   yrange=h_pv_data->GetMaximum();
//   h_pv_data->SetMaximum(2*yrange);
//   h_pv_data->SetXTitle("multiplicity");
//   h_pv_data->SetYTitle("number of vertices");
//   h_pv_data->Sumw2();
//   h_pv_data->SetMarkerStyle(20);
//   h_pv_data->SetMarkerSize(1);
//   h_pv_data->Draw("P");
//   h_PV->Draw("hist""same");
//   h_pv_data->Draw("P""same");
//   leg->Draw();
//   c4->Print("primaryvertex.png");
//   c4->Print("Plots_2.pdf");

//   TCanvas *c5 = new TCanvas("c5", "Secondary Vertex");
  
//   c5->cd();
//   yrange=h_sv_data->GetMaximum();
//   h_sv_data->SetMaximum(2*yrange);
//   h_sv_data->SetXTitle("inv. mass [GeV]");
//   h_sv_data->SetYTitle("number of vertices");
//   h_sv_data->Sumw2();
//   h_sv_data->SetMarkerStyle(20);
//   h_sv_data->SetMarkerSize(1);
//   h_sv_data->Draw("P");
//   h_SV->Draw("hist""same");
//   h_sv_data->Draw("P""same");
//   leg->Draw();
//   c5->Print("scondaryvertex.png");
//   c5->Print("Plots_2.pdf");

//   TCanvas *c6 = new TCanvas("c6", "Subjet Track PT");
  
//   c6->cd();
//   yrange=h_sjpt_data->GetMaximum();
//   h_sjpt_data->SetMaximum(2*yrange);
//   h_sjpt_data->SetXTitle("PT_{track} [GeV]");
//   h_sjpt_data->SetYTitle("number of tracks");
//   h_sjpt_data->Sumw2();
//   h_sjpt_data->SetMarkerStyle(20);
//   h_sjpt_data->SetMarkerSize(1);
//   h_sjpt_data->Draw("P");
//   h_SJ_PT->Draw("hist""same");
//   h_sjpt_data->Draw("P""same");
//   leg->Draw();
//   c6->Print("subjetpt.png");
//   c6->Print("Plots_2.pdf");
   
//   TCanvas *c7 = new TCanvas("c7", "m12");
  
//   c7->cd();
//   yrange=h_m12_data->GetMaximum();
//   h_m12_data->SetMaximum(2*yrange);
//   h_m12_data->SetXTitle("m_{12} [GeV]");
//   h_m12_data->SetYTitle("number of topjets");
//   h_m12_data->Sumw2();
//   h_m12_data->SetMarkerStyle(20);
//   h_m12_data->SetMarkerSize(1); 
//   h_m12_data->Draw("P");
//   h_M12->Draw("hist""same");
//   h_m12_data->Draw("P""same");
//   leg->Draw();
//   c7->Print("m12.png");
//   c7->Print("Plots_2.pdf");

//   TCanvas *c8 = new TCanvas("c8", "m13");
  
//   c8->cd();
//   yrange=h_m13_data->GetMaximum();
//   h_m13_data->SetMaximum(2*yrange);
//   h_m13_data->SetXTitle("m_{13} [GeV]");
//   h_m13_data->SetYTitle("number of topjets");
//   h_m13_data->Sumw2();
//   h_m13_data->SetMarkerStyle(20);
//   h_m13_data->SetMarkerSize(1); 
//   h_m13_data->Draw("P");
//   h_M13->Draw("hist""same");
//   h_m13_data->Draw("P""same");
//   leg->Draw();
//   c8->Print("m13.png");
//   c8->Print("Plots_2.pdf");

//   TCanvas *c9 = new TCanvas("c9", "m23");
  
//   c9->cd();
//   yrange=h_m23_data->GetMaximum();
//   h_m23_data->SetMaximum(2*yrange);
//   h_m23_data->SetXTitle("m_{23} [GeV]");
//   h_m23_data->SetYTitle("number of topjets");
//   h_m23_data->Sumw2();
//   h_m23_data->SetMarkerStyle(20);
//   h_m23_data->SetMarkerSize(1); 
//   h_m23_data->Draw("P");
//   h_M23->Draw("hist""same");
//   h_m23_data->Draw("P""same");
//   leg->Draw();
//   c9->Print("m23.png");
//   c9->Print("Plots_2.pdf");

//   TCanvas *c10 = new TCanvas("c10", "fRec");
  
//   c10->cd();
//   yrange=h_fRec_data->GetMaximum();
//   h_fRec_data->SetMaximum(2*yrange);
//   h_fRec_data->SetXTitle("fRec");
//   h_fRec_data->SetYTitle("number of topjets");
//   h_fRec_data->Sumw2();
//   h_fRec_data->SetMarkerStyle(20);
//   h_fRec_data->SetMarkerSize(1); 
//   h_fRec_data->Draw("P");
//   h_FREC->Draw("hist""same");
//   h_fRec_data->Draw("P""same");
//   leg->Draw();
//   c10->Print("fRec.png");
//   c10->Print("Plots_2.pdf");

//   TCanvas *c11 = new TCanvas("c11", "HTTmass");
  
//   c11->cd();
//   yrange=h_HTTmass_data->GetMaximum();
//   h_HTTmass_data->SetMaximum(2*yrange);
//   h_HTTmass_data->SetXTitle("HTTmass [GeV]");
//   h_HTTmass_data->SetYTitle("number of topjets");
//   h_HTTmass_data->Sumw2();
//   h_HTTmass_data->SetMarkerStyle(20);
//   h_HTTmass_data->SetMarkerSize(1); 
//   h_HTTmass_data->Draw("P");
//   h_HTTMASS->Draw("hist""same");
//   h_HTTmass_data->Draw("P""same");
//   leg->Draw();
//   c11->Print("HTTmass.png");
//   c11->Print("Plots_2.pdf");

//   TCanvas *c12 = new TCanvas("c12", "tau21");
  
//   c12->cd();
//   yrange=h_tau21_data->GetMaximum();
//   h_tau21_data->SetMaximum(2*yrange);
//   h_tau21_data->SetXTitle("tau21");
//   h_tau21_data->SetYTitle("number of topjets");
//   h_tau21_data->Sumw2();
//   h_tau21_data->SetMarkerStyle(20);
//   h_tau21_data->SetMarkerSize(1); 
//   h_tau21_data->Draw("P");
//   h_TAU21->Draw("hist""same");
//   h_tau21_data->Draw("P""same");
//   leg->Draw();
//   c12->Print("tau21.png");
//   c12->Print("Plots_2.pdf");

//   TCanvas *c13 = new TCanvas("c13", "tau32");
  
//   c13->cd();
//   yrange=h_tau32_data->GetMaximum();
//   h_tau32_data->SetMaximum(2*yrange);
//   h_tau32_data->SetXTitle("tau32");
//   h_tau32_data->SetYTitle("number of topjets");
//   h_tau32_data->Sumw2();
//   h_tau32_data->SetMarkerStyle(20);
//   h_tau32_data->SetMarkerSize(1); 
//   h_tau32_data->Draw("P");
//   h_TAU32->Draw("hist""same");
//   h_tau32_data->Draw("P""same");
//   leg->Draw();
//   c13->Print("tau32.png");
//   c13->Print("Plots_2.pdf");

//   TCanvas *c14 = new TCanvas("c14", "Top Mass");
  
//   c14->cd();
//   yrange=h_tm_sub_data->GetMaximum();
//   h_tm_sub_data->SetMaximum(2*yrange);
//   h_tm_sub_data->SetXTitle("m_{top} [GeV]");
//   h_tm_sub_data->SetYTitle("number of topjets");
//   h_tm_sub_data->Sumw2();
//   h_tm_sub_data->SetMarkerStyle(20);
//   h_tm_sub_data->SetMarkerSize(1); 
//   h_tm_sub_data->Draw("P");
//   h_TopMass_sub->Draw("hist""same");
//   h_tm_sub_data->Draw("P""same");
//   leg->Draw();
//   c14->Print("topmasssub.png");
//   c14->Print("Plots_2.pdf");


//  TCanvas *c15 = new TCanvas("c15", "wmass");
  
//   c15->cd();
//   yrange=h_tm_sub_data->GetMaximum();
//   h_wmass_data->SetMaximum(2*yrange);
//   h_wmass_data->SetXTitle("m_{W} [GeV]");
//   h_wmass_data->SetYTitle("number of topjets");
//   h_wmass_data->Sumw2();
//   h_wmass_data->SetMarkerStyle(20);
//   h_wmass_data->SetMarkerSize(1); 
//   h_wmass_data->Draw("P");
//   h_WMASS->Draw("hist""same");
//   h_wmass_data->Draw("P""same");
//   leg->Draw();
//   c15->Print("wmass.png");
//   c15->Print("Plots_2.pdf");
//   c15->Print("Plots_2.pdf]");






//   ofile->Close();
// }
