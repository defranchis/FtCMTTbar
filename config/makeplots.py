from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TAttFill
from array import array
#from ROOT import *
import ROOT
#setup
gROOT.SetBatch()
gStyle.SetOptStat('ioue')
flavour_names_mc = ["b","c","uds"]
flavour_names_mc_legend = ["b quark","c quark","uds quark or gluon"]
flavour_name_data = "none"
flavour_colors = [kRed,8,kBlue,5,kGray]
process_names_mc = ['MC.DYJetsToLL_M-10to50','MC.DYJetsToLL_M-50','MC.TTbar','MC.ST_t-channel','MC.ST_tW_antitop','MC.ST_tW_top','MC.WJets'] 
#process_names_mc = ['MC.DYJetsToLL_M-10to50']
process_name_data = "DATA.Data"
histogram_names = ["subCSV","subFlavour","subTrackMomentum","subTrackEta","subTrackEtaRel","subTrackDeltaR","subTrackSip3dVal","subTrackSip3dSig","subTrackSip2dVal","subTrackSip2dSig","subTrackDecayLenVal","subTrackChi2","subTrackNTotalHits","subTrackNPixelHits","subTrackPtRel","subTrackPPar","subTrackPtRatio","subTrackPParRatio","subTrackJetDistVal","subTrackJetDistSig","subTrackGhostTrackDistVal","subTrackGhostTrackDistSig","subTrackGhostTrackWeight","subFlightDistance2dVal","subFlightDistance2dSig","subFlightDistance3dVal","subFlightDistance3dSig","subVertexJetDeltaR","subJetNSecondaryVertices","subVertexNTracks","subSecondaryVertex","subVertexChi2","subVertexNdof","subVertexNormalizedChi2","subVertexCategoryJTC","subVertexMassJTC","subVertexEnergyRatioJTC","subTrackSip3dSigAboveCharmJTC","subTrackMultiplicity","subTrackPt"]
histogram_descriptions = ["combined secondary vertex discriminator of the subjet","matched flavour of the subjet","momentum of tracks in the subjet","pseudorapidity of tracks in the subjet","track pseudorapidity, relative to the jet axis","track pseudoangular distance from the jet axis","track 3D signed impact parameter","track 3D signed impact parameter significance","track 2D signed impact parameter","track 2D signed impact parameter significance","track decay length","track fit chi2","number of valid total hits","number of valid pixel hits","track transverse momentum, relative to the jet axis","track parallel momentum, along the jet axis","track transverse momentum, relative to the jet axis, normalized to its energy","track parallel momentum, along the jet axis, normalized to its energy","minimum track approach distance to jet axis","minimum track approach distance to jet axis significance","minimum approach distance to ghost track","minimum approach distance to ghost track significance","weight of track participation in ghost track fit","transverse distance between primary and secondary vertex","transverse distance significance between primary and secondary vertex","distance between primary and secondary vertex","distance significance between primary and secondary vertex","pseudoangular distance between jet axis and secondary vertex direction","number of reconstructed possible secondary vertices in jet","number of tracks at secondary vertex","secondary vertex uncorrected mass","secondary vertex chi2","secondary vertex fit dergrees of frendom","secondary vertex fit normalized chi2","secondary vertex category from jet tag computer","secondary vertex corrected mass from jet tag computer","ratio of energy at secondary vertex over total energy from JTC","track 3D signed impact parameter significance of first track lifting mass above charm from JTC","track multiplicity of the subjet","track transverse momentum"]
#histogram_names = ["subCSV"]
#histogram_descriptions = ["matched flavour of the subjet"]

#yaxis_tracks = 'N of tracks'
#yaxis_vertices = 'N of vertices'
#yaxis_subjets = 'N of subjets'
yaxis_tracks = 'Entries'
yaxis_vertices = 'Entries'
yaxis_subjets = 'Entries'
histogram_yaxes = [yaxis_subjets for i in range(2)] + [yaxis_tracks for i in range(21)] + [yaxis_vertices for i in range(5)] + [yaxis_subjets] + [yaxis_vertices for i in range(6)] + [yaxis_vertices for i in range(4)] + [yaxis_subjets] + [yaxis_tracks]+ ['Events']
#histogram_xaxes = ["particle ID", "p [GeV/c]"]
histogram_xaxes = ["CSVv2 discriminator", "particle ID", "Track p [GeV]", "#eta", "#Delta #eta(track,jet axis)", "#Delta R(track,jet axis)", "3D IP of tracks", "3D IP significance of tracks", "2D IP of tracks", "2D IP significance of tracks", "L_{d} [cm]", "#chi^2_{track}", "Number of hits", "Number of pixel hits","pT relative to jet axis [GeV] ","parallel momentum along jet axis [GeV] ","normalized pT relative to jet axis","normalized parallel momentum along jet axis","d [cm]"," d/#sigma_{d}","d_{ghost} [cm]","d_{ghost}/#sigma_{d_{ghost}}"," weight of track participation in ghost track fit", "dist_{T}(PV,SV) [cm]", "dist_{T}/#sigma_{dist_{T}}(PV,SV)", "dist(PV,SV) [cm]", "SV 3D flight distance significance", "#Delta#phi", "Number of SV", "N_{tracks}", "uncorrected inv. mass [GeV]", "#chi^2_{SV}", "N_{dof}", "#chi^2/N_{dof}(SV)", "category", "inv. mass [GeV]", "E_{SV}/E_{tot}", "IP/#sigma_{IP}","Number of selected tracks in the jets","pT [GeV]"]
files_path = "/nfs/dust/cms/user/schumas/sframe/CMSSW_7_4_7/src/UHH2/FtCMTTbar/config/"
#files_path = "/nfs/dust/cms/user/marchesi/74XUHH2/CMSSW_7_4_7/src/UHH2/FtCMTTbar/config/"
files_name_base = "uhh2.AnalysisModuleRunner"
cut_name = "AfterCuts"

#get the files
files_list_mc=[]
for process_name_index in range(len(process_names_mc)):
  process_name=process_names_mc[process_name_index]
  files_list_mc.append(TFile(files_path+"/"+files_name_base+"."+process_name+".root"))
  
  
file_data=TFile(files_path+"/"+files_name_base+"."+process_name_data+".root")



#open output file
outfile=TFile("subjethistos.root", "RECREATE")


#get mc histos
input_histos_mc=[]

for process_name_index in range(len(process_names_mc)):
  histo_file=files_list_mc[process_name_index]
  process_name=process_names_mc[process_name_index]
  tmp_process_sublist=[]
  
  for histogram_name_index in range(len(histogram_names)):
    histogram_name=histogram_names[histogram_name_index]
    tmp_histogram_sublist=[]
    for flavour_name_index in range(len(flavour_names_mc)):
      flavour_name=flavour_names_mc[flavour_name_index]
      flavour_color=flavour_colors[flavour_name_index]
      if flavour_name not in ["uds"]:
        tmp_histogram_sublist.append(histo_file.Get(cut_name+"/"+histogram_name+"_"+flavour_name))#.Clone())
      else:
        tmp_uds = histo_file.Get(cut_name+"/"+histogram_name+"_"+flavour_name)
        tmp_g = histo_file.Get(cut_name+"/"+histogram_name+"_g")
        print "before", tmp_uds.Integral()
        tmp_uds.Add(tmp_g)
        print "after", tmp_uds.Integral()
        tmp_histogram_sublist.append(tmp_uds)
      #histo_file.Get(cut_name+"/"+histogram_name+"_"+flavour_name).Write()
      nx = tmp_histogram_sublist[-1].GetNbinsX()
      tmp_histogram_sublist[-1].Fill(tmp_histogram_sublist[-1].GetBinCenter(nx), tmp_histogram_sublist[-1].GetBinContent(nx+1))
      tmp_histogram_sublist[-1].SetFillColor(flavour_color)
      tmp_histogram_sublist[-1].SetLineColor(kBlack)
      tmp_histogram_sublist[-1].SetMarkerColor(flavour_color)
      if histogram_name not in ["subTrackMultiplicity","subTrackSip3dSig","subFlightDistance3dSig","subTrackNPixelHits","subTrackNTotalHits","subJetNSecondaryVertices","subVertexNTracks","subCSV"]:
        tmp_histogram_sublist[-1].Rebin(2)
      elif histogram_name in ["subCSV"]:
        tmp_histogram_sublist[-1].Rebin(5)
      elif histogram_name in ["subFlightDistance3dSig"]: 
         tmp_histogram_sublist[-1].Rebin(2) 
         #inning = [0, 1.6, 3.2, 6.4, 12.8, 19.2,25.6,33.6, 57.6, 80 ]
         #mp_histogram_sublist[-1] = tmp_histogram_sublist[-1].Rebin(9,"subFlightDistance3dSig",array('d',binning))
      elif histogram_name in ["subTrackSip3dSig"]: 
        tmp_histogram_sublist[-1].Rebin(2)
        tmp_histogram_sublist[-1].GetXaxis().SetRangeUser(-10, 10)
        #print "#######################"
        tmp_histogram_sublist[-1].Draw()
        ROOT.gPad.SaveAs("test.pdf")
      elif histogram_name in ["subTrackMultiplicity"]:
 
        binning = [0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,30 ]
        tmp_histogram_sublist[-1] = tmp_histogram_sublist[-1].Rebin(16,"subTrackMultiplicity",array('d',binning))
        tmp_histogram_sublist[-1].GetXaxis().SetRangeUser(0, 15)
      #if histogram_name in ["subTrackNPixelHits",]:

    tmp_process_sublist.append(tmp_histogram_sublist)  
  input_histos_mc.append(tmp_process_sublist)
#structure: input_histos_mc[process_name_index][histogram_name_index][flavour_name_index]
 


#get data histos
input_histos_data=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  input_histos_data.append(file_data.Get(cut_name+"/"+histogram_name+"_"+flavour_name_data))#.Clone())
  nx = input_histos_data[-1].GetNbinsX()
  input_histos_data[-1].Fill(input_histos_data[-1].GetBinCenter(nx), input_histos_data[-1].GetBinContent(nx+1))
  input_histos_data[-1].SetLineStyle(1)
  input_histos_data[-1].SetLineColor(1)
  input_histos_data[-1].SetLineWidth(2)
  input_histos_data[-1].SetMarkerColor(1)
  input_histos_data[-1].SetMarkerStyle(20)
  input_histos_data[-1].SetMarkerSize(0.75)
  if histogram_name not in ["subTrackMultiplicity","subTrackSip3dSig","subFlightDistance3dSig","subTrackNPixelHits","subTrackNTotalHits","subJetNSecondaryVertices","subVertexNTracks","subCSV"]:
    input_histos_data[-1].Rebin(2)                                                                                                                                        
  elif histogram_name in ["subCSV"]:                                                                                                                                           
    input_histos_data[-1].Rebin(5)
  elif histogram_name in ["subFlightDistance3dSig"]: 
    input_histos_data[-1].Rebin(2)
     #inning = [0, 1.6, 3.2, 6.4, 12.8, 19.2,25.6,33.6, 57.6, 80 ]
     #nput_histos_data[-1] = input_histos_data[-1].Rebin(9,"subFlightDistance3dSig",array('d',binning))
  elif histogram_name in ["subTrackSip3dSig"]:                                                                                           
    input_histos_data[-1].Rebin(2)
    input_histos_data[-1].GetXaxis().SetRangeUser(-10, 10)
  elif histogram_name in ["subTrackMultiplicity"]:
    binning = [0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,30 ]
    input_histos_data[-1] = input_histos_data[-1].Rebin(16,"subTrackMultiplicity",array('d',binning))
    input_histos_data[-1].GetXaxis().SetRangeUser(0, 15)
  input_histos_data[-1].Sumw2()
  input_histos_data[-1].Write()
#structure: input_histos_data[histogram_name_index]

#merge mc histos
input_merged_mc=[]
for histogram_name_index in range(len(histogram_names)):
  tmp_histogram_sublist=[]
  for flavour_name_index in range(len(flavour_names_mc)):
    tmp_merged_histo=input_histos_mc[0][histogram_name_index][flavour_name_index].Clone(histogram_names[histogram_name_index]+'_'+flavour_names_mc[flavour_name_index]+'_Merge')
    if len(input_histos_mc)>1:
      for process_name_index in range(1,len(process_names_mc)):
	tmp_merged_histo.Add(input_histos_mc[process_name_index][histogram_name_index][flavour_name_index])
    tmp_merged_histo.Sumw2()
    tmp_histogram_sublist.append(tmp_merged_histo)
#    tmp_merged_histo.Write()
  input_merged_mc.append(tmp_histogram_sublist)
#structure: input_merged_mc[histogram_name_index][flavour_name_index]
  
#stack mc histos
stacked_mc=[]
for histogram_name_index in range(len(histogram_names)):
  tmp_stack=THStack(histogram_names[histogram_name_index]+'_Stack','')
  for flavour_name_index in range(len(flavour_names_mc)):
    #input_merged_mc[histogram_name_index][flavour_name_index].GetYaxis().SetRangeUser(0,1000000)
    tmp_stack.Add(input_merged_mc[histogram_name_index][flavour_name_index])
  stacked_mc.append(tmp_stack)
#  stacked_mc[-1].Write()
#structure: stacked_mc[histogram_name_index]

#add mc histos for pull
added_mc=[]
for histogram_name_index in range(len(histogram_names)):
  tmp_added=input_merged_mc[histogram_name_index][0].Clone(histogram_names[histogram_name_index]+'_Add')
  for flavour_name_index in range(1,len(flavour_names_mc)):
    tmp_added.Add(input_merged_mc[histogram_name_index][flavour_name_index])
  #if histogram_name in ["subTrackSip3dSig"]:                                                                                           
    #tmp_added.SetAxisRange(-10, 10, "X")
  tmp_added.Sumw2()
  tmp_added.SetTitle('')
#  tmp_added.SetTitle(histogram_descriptions[histogram_name_index])
  tmp_added.Write()
  added_mc.append(tmp_added)
#structure: added_mc[histogram_name_index]

#make pull
pulls=[]
for histogram_name_index in range(len(histogram_names)):
  tmp_pull=input_histos_data[histogram_name_index].Clone(histogram_names[histogram_name_index]+'_Pull')
  tmp_pull.Divide(added_mc[histogram_name_index])
  tmp_pull.SetStats(kFALSE)
  tmp_pull.SetTitle('')
  tmp_pull.SetFillColor(1)
  tmp_pull.SetFillStyle(0)
  tmp_pull.SetLineWidth(2)
  tmp_pull.SetMarkerStyle(20)
  tmp_pull.SetMarkerSize(0.75)
  tmp_pull.GetYaxis().SetLabelSize(0.12)
  tmp_pull.GetYaxis().SetLabelFont(42)
  tmp_pull.GetYaxis().SetTitle("Data / MC")
  tmp_pull.GetYaxis().SetTitleSize(0.14)
  tmp_pull.GetYaxis().SetTitleOffset(0.31)
  tmp_pull.GetYaxis().SetRangeUser(0.0,2.0)
  if histogram_name in ["subTrackSip3dSig"]: 
    tmp_pull.GetXaxis().SetRangeUser(-10, 10)
  tmp_pull.GetYaxis().SetNdivisions(3,2,0)
  tmp_pull.GetXaxis().SetLabelSize(0.12)
  if histogram_name in ["subCSV"]:
    tmp_pull.GetXaxis().SetTitle("Jets/0.05")
  elif histogram_name in ["subFlightDistance3dSig"]:
    tmp_pull.GetXaxis().SetTitle("SVs/1.6")
  elif histogram_name in ["subJetNSecondaryVertices"]:
    tmp_pull.GetXaxis().SetTitle("SVs")
  elif histogram_name in ["subTrackMultiplicity"]:
    tmp_pull.GetXaxis().SetTitle("Jets")
  elif histogram_name in ["subTrackNPixelHits"]:
    tmp_pull.GetXaxis().SetTitle("Tracks")
  elif histogram_name in ["subTrackSip3dSig"]:
    tmp_pull.GetXaxis().SetTitle("Tracks/1.4")
  else:
    tmp_pull.GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
  tmp_pull.GetXaxis().SetTitleSize(0.15)
  tmp_pull.GetXaxis().SetTitleOffset(0.9)
  tmp_pull.GetXaxis().SetLabelFont(42)

  tmp_pull.SetLineColor(1)
  tmp_pull.SetLineWidth(2)
  tmp_pull.Sumw2()
  pulls.append(tmp_pull)

#compare mc and data
#canvases=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  tmp_canvas=TCanvas(histogram_name+'_Canvas','')
  gStyle.SetOptFit(1)
  gStyle.SetOptStat(0)
  gStyle.SetOptTitle(0)
  tmp_canvas.Range(0,0,1,1)
  tmp_canvas.SetFillColor(10)
  tmp_canvas.SetBorderMode(0)
  tmp_canvas.SetBorderSize(2)
  tmp_canvas.SetTickx(1)
  tmp_canvas.SetTicky(1)
  tmp_canvas.SetLeftMargin(0.16)
  tmp_canvas.SetRightMargin(0.02)
  tmp_canvas.SetTopMargin(0.05)
  tmp_canvas.SetBottomMargin(0.13)
  tmp_canvas.SetFrameFillColor(0)
  tmp_canvas.SetFrameFillStyle(0)
  tmp_canvas.SetFrameBorderMode(0)
  tmp_canvas.Divide(1,2)

  top_pad=tmp_canvas.GetPad(1)
  top_pad.SetPad( 0.0, 0.25, 1.0, 1.0 )
  top_pad.Range(-1.560975,-1.463546,8.195122,7.478885)
  top_pad.SetFillColor(0)
  top_pad.SetBorderMode(0)
  top_pad.SetBorderSize(2)
  #top_pad.SetLogy()
  top_pad.SetTickx(1)
  top_pad.SetTicky(1)
  top_pad.SetLeftMargin(0.16)
  top_pad.SetRightMargin(0.02)
  top_pad.SetTopMargin(0.065)
  top_pad.SetBottomMargin(0.13)
  top_pad.SetFrameFillStyle(0)
  top_pad.SetFrameBorderMode(0)
  top_pad.SetFrameFillStyle(0)
  top_pad.SetFrameBorderMode(0)

  bottom_pad=tmp_canvas.GetPad(2)
  bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.32 )
  bottom_pad.Range(-1.560975,-0.18125,8.195122,1.69375)
  bottom_pad.SetFillColor(0)
  bottom_pad.SetBorderMode(0)
  bottom_pad.SetBorderSize(2)
  bottom_pad.SetGridy()
  bottom_pad.SetTickx(1)
  bottom_pad.SetTicky(1)
  bottom_pad.SetLeftMargin(0.16)
  bottom_pad.SetRightMargin(0.02)
  bottom_pad.SetTopMargin(0.05)
  bottom_pad.SetBottomMargin(0.31)
  bottom_pad.SetFrameFillStyle(0)
  bottom_pad.SetFrameBorderMode(0)
  bottom_pad.SetFrameFillStyle(0)
  bottom_pad.SetFrameBorderMode(0)
 


  tmp_canvas.cd(1)
  if histogram_name in ["subTrackSip3dSig"]: 
    stacked_mc[histogram_name_index].Draw()
    stacked_mc[histogram_name_index].GetXaxis().SetRangeUser(-10, 10)
  yrange=stacked_mc[histogram_name_index].GetMaximum();
  if histogram_name in ["subTrackMomentum","subTrackJetDistVal","subTrackDecayLenVal","subJetNSecondaryVertices","subCSV","subTrackSip3dSig","subTrackSip3dVal"]:
    stacked_mc[histogram_name_index].SetMaximum(100*yrange)
  elif histogram_name in ["subFlightDistance3dSig"]:
    stacked_mc[histogram_name_index].SetMaximum(10000*yrange)
  elif histogram_name in ["subTrackMultiplicity"]:
    stacked_mc[histogram_name_index].Draw()
    stacked_mc[histogram_name_index].GetXaxis().SetRangeUser(0, 15)
    stacked_mc[histogram_name_index].SetMaximum(3*yrange) 
  elif histogram_name in ["subTrackNPixelHits"]:
    stacked_mc[histogram_name_index].SetMaximum(24*yrange)
  elif histogram_name in ["subTrackSip3dSig"]:
    stacked_mc[histogram_name_index].SetMaximum(2*yrange)
  else:
    stacked_mc[histogram_name_index].SetMaximum(2*yrange)
  stacked_mc[histogram_name_index].Draw("hist")
  if histogram_name in["subFlightDistance3dSig"]:
    input_histos_data[histogram_name_index].Draw("same e X0")
  else:
    input_histos_data[histogram_name_index].Draw("same e X0")
  if histogram_name in ["subTrackSip3dSig","subTrackSip3dVal"]:
    legend=TLegend(0.655,0.55,0.955,0.9)
  else:
    legend=TLegend(0.555,0.55,0.955,0.9)
  legend.SetBorderSize(0)
  legend.SetTextFont(62)
  legend.SetTextSize(0.05)
  legend.SetLineColor(1)
  legend.SetLineStyle(1)
  legend.SetLineWidth(1)
  legend.SetFillColor(0)
  legend.SetFillStyle(1001)
    
  legend.AddEntry(input_histos_data[0],"Data",'e x0 p')
  for flavour_name_index in range(len(flavour_names_mc)):
    legend.AddEntry(input_merged_mc[0][flavour_name_index],flavour_names_mc_legend[flavour_name_index],'f')
  legend.Draw()
  if stacked_mc[histogram_name_index].GetMaximum() != 0:
  #stacked_mc[histogram_name_index].GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
    stacked_mc[histogram_name_index].GetYaxis().SetTitle(histogram_yaxes[histogram_name_index])
    if histogram_name in ["subCSV"]:     
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("Jets/0.05")                    
    elif histogram_name in ["subFlightDistance3dSig"]: 
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("SVs/1.6")                             
    elif histogram_name in ["subJetNSecondaryVertices"]:      
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("SVs")      
    elif histogram_name in ["subTrackMultiplicity"]:  
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("Jets")       
    elif histogram_name in ["subTrackNPixelHits"]:               
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("Tracks")                                                                          
    elif histogram_name in ["subTrackSip3dSig"]:     
      stacked_mc[histogram_name_index].GetYaxis().SetTitle("Tracks/1.4")                                          
                         
    stacked_mc[histogram_name_index].GetXaxis().SetTitle('')
    stacked_mc[histogram_name_index].GetXaxis().SetLabelOffset(9999)
    stacked_mc[histogram_name_index].GetXaxis().SetLabelSize(0.035)
    stacked_mc[histogram_name_index].GetXaxis().SetLabelFont(42)
    stacked_mc[histogram_name_index].GetXaxis().SetTitleSize(0.035)
    #stacked_mc[histogram_name_index].SetTitle(histogram_descriptions[histogram_name_index])
    stacked_mc[histogram_name_index].GetYaxis().SetTitleSize(0.06)
    stacked_mc[histogram_name_index].GetYaxis().SetLabelSize(0.05)
    stacked_mc[histogram_name_index].GetYaxis().SetTitleOffset(0.81)
    stacked_mc[histogram_name_index].GetYaxis().SetTitleFont(42)
    stacked_mc[histogram_name_index].GetYaxis().SetLabelFont(42)
    #cmslabel.Draw()
    text3 = TLatex(0.1969,0.906825,"CMS")
    text3.SetNDC();
    text3.SetTextAlign(13);
    text3.SetTextFont(61);
    text3.SetTextSize(0.07475);
    text3.SetLineWidth(2);
    text3.Draw();
    text2 = TLatex(0.1969,0.817125,"Preliminary");
    text2.SetNDC();
    text2.SetTextAlign(13);
    text2.SetTextFont(52);
    text2.SetTextSize(0.05681);
    text2.SetLineWidth(2); 
    text2.Draw();
    text4 = TLatex(0.1969,0.727425, "t#bar{t} sample")
    text4.SetNDC();
    text4.SetTextAlign(12);
    text4.SetTextFont(42);
    text4.SetTextSize(0.05681);
    text4.SetLineWidth(2);
    text4.Draw();
    text6 = TLatex(0.1969,0.668725, "HepTopTagger subjets ")
    text6.SetNDC();
    text6.SetTextAlign(12);
    text6.SetTextFont(42);
    text6.SetTextSize(0.05681);
    text6.SetLineWidth(2);
    text6.Draw();
    text7 = TLatex(0.1969,0.603725, "CA15 jets, p_{T} > 150 GeV")
    text7.SetNDC();
    text7.SetTextAlign(12);
    text7.SetTextFont(42);
    text7.SetTextSize(0.05681);
    text7.SetLineWidth(2);
    text7.Draw();
    text5 = TLatex(0.98,0.95125,"#sqrt{s} = 13 TeV, 25 ns")
    text5.SetNDC();
    text5.SetTextAlign(31);
    text5.SetTextFont(42); 
    text5.SetTextSize(0.04875);  
    text5.SetLineWidth(2); 
    text5.Draw();
    tmp_canvas.cd(2)
    if histogram_name in ["subFlightDistance3dSig"]:
      pulls[histogram_name_index].Draw("e1 X0")
    else:
      pulls[histogram_name_index].Draw("e1 x0")
    if histogram_name in ["subTrackSip3dSig"]:  
      line1=TLine(-10,1.0,10,1.0)
      line1.SetLineStyle(2)
      line1.Draw()
      line2=TLine(-10,2.0,10,2.0)
      line2.SetLineStyle(2)
      line2.Draw()
    else:
      line1=TLine(stacked_mc[histogram_name_index].GetXaxis().	GetXmin(),1.0,stacked_mc[histogram_name_index].GetXaxis().	GetXmax(),1.0)
      line1.SetLineStyle(2)
      line1.Draw()
      line2=TLine(stacked_mc[histogram_name_index].GetXaxis().	GetXmin(),2.0,stacked_mc[histogram_name_index].GetXaxis().	GetXmax(),2.0)
      line2.SetLineStyle(2)
      line2.Draw()
  #  canvases.append(tmp_canvas)
    if histogram_name in ["subTrackNPixelHits","subTrackMomentum","subTrackJetDistVal","subTrackDecayLenVal","subTrackSip3dVal","subTrackSip3dSig","subJetNSecondaryVertices","subCSV","subFlightDistance3dSig","subFlightDistance3dVal"]:
      top_pad.SetLogy()
    if histogram_name in ["subFlightDistance3dSig"]:
      top_pad.SetLogx()
      bottom_pad.SetLogx()
    #if histogram_name in ["subTrackNPixelHits","subTrackNTotalHits","subTrackMomentum","subTrackMultiplicity","subTrackSip3dVal","subTrackSip3dSig","subTrackSip2dVal","subTrackSip2dSig","subTrackJetDistVal","subTrackDeltaR","subJetNSecondaryVertices","subVertexNTracks","subVertexJetDeltaR","subCSV","subFlightDistance3dVal","subFlightDistance3dSig","subFlightDistance2dVal","subFlightDistance2dSig","subSecondaryVertex"]:
      #tmp_canvas.SaveAs('/afs/desy.de/user/s/schumas/sschuman/notes/AN-15-189/trunk/figures/CommissioningBoostedJets/z'+histogram_name+'_'+'Canvas.pdf')
    #if histogram_name in ["subTrackNPixelHits","subTrackMultiplicity","subTrackSip3dSig","subJetNSecondaryVertices","subCSV","subFlightDistance3dSig"]:
      #tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.png')
      #tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.pdf')

        #tmp_canvas.SaveAs('/afs/desy.de/user/m/marchesi/www/z'+histogram_name+'_'+'Canvas.pdf')   
    if histogram_name_index == 0:
      tmp_canvas.SaveAs('z_Canvas_2.pdf[')
    tmp_canvas.SaveAs('z_Canvas_2.pdf[')
    tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.png')
    tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.pdf')

  if  histogram_name_index == len(histogram_names)-1:
    tmp_canvas.SaveAs('z_Canvas_2.pdf]')
    tmp_canvas.Write()
      


#close file  
outfile.Close()
