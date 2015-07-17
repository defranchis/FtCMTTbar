from ROOT import TFile,TH1F,THStack,TCanvas,TLegend,TLatex,gROOT,kRed,kBlue,kGreen,kGray,kBlack,kOrange,gStyle,kTRUE,kFALSE,TLine,TAttFill

#from ROOT import *

#setup
gROOT.SetBatch()
gStyle.SetOptStat('ioue')
flavour_names_mc = ["b","c","uds","g","none"]
flavour_name_data = "data"
flavour_colors = [kRed,8,kBlue,kOrange-3,kGray]
#process_names_mc = ['MC.TTbar','MC.Wjets'] 
process_names_mc = ['MC.Test']
process_name_data = "DATA.DATA"
histogram_names = ["subCSV","subFlavour","subTrackMomentum","subTrackEta","subTrackEtaRel","subTrackDeltaR","subTrackSip3dVal","subTrackSip3dSig","subTrackSip2dVal","subTrackSip2dSig","subTrackDecayLenVal","subTrackChi2","subTrackNTotalHits","subTrackNPixelHits","subTrackPtRel","subTrackPPar","subTrackPtRatio","subTrackPParRatio","subTrackJetDistVal","subTrackJetDistSig","subTrackGhostTrackDistVal","subTrackGhostTrackDistSig","subTrackGhostTrackWeight","subFlightDistance2dVal","subFlightDistance2dSig","subFlightDistance3dVal","subFlightDistance3dSig","subVertexJetDeltaR","subJetNSecondaryVertices","subVertexNTracks","subSecondaryVertex","subVertexChi2","subVertexNdof","subVertexNormalizedChi2","subVertexCategoryJTC","subVertexMassJTC","subVertexEnergyRatioJTC","subTrackSip3dSigAboveCharmJTC","subTrackMultiplicity","subTrackPt","MassTop"]
histogram_descriptions = ["combined secondary vertex discriminator of the subjet","matched flavour of the subjet","momentum of tracks in the subjet","pseudorapidity of tracks in the subjet","track pseudorapidity, relative to the jet axis","track pseudoangular distance from the jet axis","track 3D signed impact parameter","track 3D signed impact parameter significance","track 2D signed impact parameter","track 2D signed impact parameter significance","track decay length","track fit chi2","number of valid total hits","number of valid pixel hits","track transverse momentum, relative to the jet axis","track parallel momentum, along the jet axis","track transverse momentum, relative to the jet axis, normalized to its energy","track parallel momentum, along the jet axis, normalized to its energy","minimum track approach distance to jet axis","minimum track approach distance to jet axis significance","minimum approach distance to ghost track","minimum approach distance to ghost track significance","weight of track participation in ghost track fit","transverse distance between primary and secondary vertex","transverse distance significance between primary and secondary vertex","distance between primary and secondary vertex","distance significance between primary and secondary vertex","pseudoangular distance between jet axis and secondary vertex direction","number of reconstructed possible secondary vertices in jet","number of tracks at secondary vertex","secondary vertex uncorrected mass","secondary vertex chi2","secondary vertex fit dergrees of frendom","secondary vertex fit normalized chi2","secondary vertex category from jet tag computer","secondary vertex corrected mass from jet tag computer","ratio of energy at secondary vertex over total energy from JTC","track 3D signed impact parameter significance of first track lifting mass above charm from JTC","track multiplicity of the subjet","track transverse momentum","Top Mass"]
#histogram_names = ["subCSV"]
#histogram_descriptions = ["matched flavour of the subjet"]

yaxis_tracks = 'N of tracks'
yaxis_vertices = 'N of vertices'
yaxis_subjets = 'N of subjets'
histogram_yaxes = [yaxis_subjets for i in range(2)] + [yaxis_tracks for i in range(21)] + [yaxis_vertices for i in range(5)] + [yaxis_subjets] + [yaxis_vertices for i in range(6)] + [yaxis_vertices for i in range(4)] + [yaxis_subjets] + [yaxis_tracks]+ ['Events']
#histogram_xaxes = ["particle ID", "p [GeV/c]"]
histogram_xaxes = ["CSV discriminator", "particle ID", "p [GeV/c]", "#eta", "#Delta#eta(track,jet axis)", "#Delta#phi(track,jet axis)", "IP [cm]", "IP/#sigma_{IP}", "IP_{2D} [cm]", "IP_{2D}/#sigma_{IP_{2D}}", "L_{d} [cm]", "#chi^2_{track}", "N_{hits}", "N_{pixel hits}"," "," "," "," ","d [cm]"," "," "," "," ", "dist_T(SV_1,SV_2) [cm]", "dist_T/#sigma_{dist_T}(SV_1,SV_2)", "dist(SV_1,SV_2) [cm]", "dist/#sigma_{dist}(PV,SV)", "#Delta#phi", "N of vertices", "N tracks", "inv. mass [GeV/c^2]", "#chi^2_{SV}", "N_{dof}", "#chi^2/N_{dof}(SV)", "category", "inv. mass [GeV/c^{2}]", "E_{SV}/E_{tot}", "IP/#sigma_{IP}","N of tracks in the subjet","pT [GeV/c]","Mass [GeV]"]
files_path = "/nfs/dust/cms/user/schumas/sframe/CMSSW_7_4_3/src/UHH2/FtCMTTbar/config/"
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
      tmp_histogram_sublist.append(histo_file.Get(cut_name+"/"+histogram_name+"_"+flavour_name))#.Clone())
      #histo_file.Get(cut_name+"/"+histogram_name+"_"+flavour_name).Write()
      tmp_histogram_sublist[-1].SetFillColor(flavour_color)
      tmp_histogram_sublist[-1].SetLineColor(kBlack)
      tmp_histogram_sublist[-1].SetMarkerColor(flavour_color)
      tmp_histogram_sublist[-1].Sumw2()
      

    tmp_process_sublist.append(tmp_histogram_sublist)  
  input_histos_mc.append(tmp_process_sublist)
#structure: input_histos_mc[process_name_index][histogram_name_index][flavour_name_index]
 


#get data histos
input_histos_data=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  input_histos_data.append(file_data.Get(cut_name+"/"+histogram_name+"_"+flavour_name_data))#.Clone())
  input_histos_data[-1].SetLineColor(kBlack)
  input_histos_data[-1].SetLineWidth(2)
  input_histos_data[-1].SetMarkerColor(kBlack)
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
  tmp_added.Sumw2()
  tmp_added.SetTitle(histogram_descriptions[histogram_name_index])
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
  tmp_pull.GetYaxis().SetLabelSize(0.22)
  tmp_pull.GetYaxis().SetTitle("Data / MC")
  tmp_pull.GetYaxis().SetTitleSize(0.22)
  tmp_pull.GetYaxis().SetTitleOffset(0.23)
  tmp_pull.GetYaxis().SetRangeUser(0.5,1.7)
  tmp_pull.GetYaxis().SetNdivisions(3,2,0)
  tmp_pull.GetXaxis().SetLabelSize(0.22)
  tmp_pull.GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
  tmp_pull.GetXaxis().SetTitleSize(0.22)
  tmp_pull.GetXaxis().SetTitleOffset(0.9)
  tmp_pull.SetLineColor(kBlue+2)
  tmp_pull.SetLineWidth(2)
  tmp_pull.Sumw2()
  pulls.append(tmp_pull)

#make legend
legend=TLegend(0.9,0.295,0.999,0.93)
for flavour_name_index in range(len(flavour_names_mc)):
  legend.AddEntry(input_merged_mc[0][flavour_name_index],flavour_names_mc[flavour_name_index],'f')
legend.AddEntry(input_histos_data[0],flavour_name_data,'lpe')
cmslabel=TLatex(0.3,0.87,"CMS Preliminary #sqrt{s} = 8TeV  15.9 fb^{-1}")
cmslabel.SetNDC()

#compare mc and data
#canvases=[]
for histogram_name_index in range(len(histogram_names)):
  histogram_name=histogram_names[histogram_name_index]
  tmp_canvas=TCanvas(histogram_name+'_Canvas','')
  tmp_canvas.Divide(1,2)
  top_pad=tmp_canvas.GetPad(1)
  bottom_pad=tmp_canvas.GetPad(2)
  top_pad.SetPad( 0.0, 0.25, 1.0, 1.0 )
  bottom_pad.SetPad( 0.0, 0.0, 1.0, 0.25 )
  top_pad.SetTopMargin(0.07)
  #top_pad.SetBottomMargin(0.03)
  top_pad.SetBottomMargin(0.0)#0.013)
  top_pad.SetLeftMargin(0.12)
  top_pad.SetRightMargin(0.1)
  #bottom_pad.SetTopMargin(0.03)
  bottom_pad.SetTopMargin(0.0)
  bottom_pad.SetBottomMargin(0.42)
  bottom_pad.SetLeftMargin(0.12)
  bottom_pad.SetRightMargin(0.1)
  tmp_canvas.cd(1)
  stacked_mc[histogram_name_index].Draw("hist")
  input_histos_data[histogram_name_index].Draw("same")
  legend.Draw()
  if stacked_mc[histogram_name_index].GetMaximum() != 0:
  #stacked_mc[histogram_name_index].GetXaxis().SetTitle(histogram_xaxes[histogram_name_index])
    stacked_mc[histogram_name_index].GetYaxis().SetTitle(histogram_yaxes[histogram_name_index])
    stacked_mc[histogram_name_index].GetXaxis().SetTitle('')
    stacked_mc[histogram_name_index].GetXaxis().SetLabelOffset(9999)
    stacked_mc[histogram_name_index].GetXaxis().SetLabelSize(0)
    stacked_mc[histogram_name_index].SetTitle(histogram_descriptions[histogram_name_index])
    stacked_mc[histogram_name_index].GetYaxis().SetTitleSize(0.07)
    stacked_mc[histogram_name_index].GetYaxis().SetLabelSize(0.07)
    stacked_mc[histogram_name_index].GetYaxis().SetTitleOffset(0.9)
    cmslabel.Draw()
    tmp_canvas.cd(2)
    pulls[histogram_name_index].Draw()
    line1=TLine(stacked_mc[histogram_name_index].GetXaxis().	GetXmin(),1.0,stacked_mc[histogram_name_index].GetXaxis().	GetXmax(),1.0)
    line1.SetLineStyle(2)
    line1.Draw()
    line2=TLine(stacked_mc[histogram_name_index].GetXaxis().	GetXmin(),2.0,stacked_mc[histogram_name_index].GetXaxis().	GetXmax(),2.0)
    line2.SetLineStyle(2)
    line2.Draw()
  #  canvases.append(tmp_canvas)
    if histogram_name in ["subTrackNPixelHits","subTrackMomentum","subTrackJetDistVal","subTrackDecayLenVal","subTrackSip3dVal","subTrackSip3dSig","subJetNSecondaryVertices","subCSV","subFlightDistance3dSig"]:
      top_pad.SetLogy()
 # if histogram_name in ["subTrackNPixelHits","subTrackMomentum","subTrackJetDistVal","subTrackDecayLenVal","subTrackSip3dVal","subTrackSip3dSig","subFlightDistance3dSig","subVertexMassJTC","subJetNSecondaryVertices","subVertexNTracks","subCSV","subTrackMultiplicity"]:#["subTrackMomentum","subTrackSip3dSig","subFlightDistance3dSig","subCSV"]:
      
    tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.png')
    tmp_canvas.SaveAs('z'+histogram_name+'_'+'Canvas.pdf')
    tmp_canvas.Write()
      
#close file  
outfile.Close()
