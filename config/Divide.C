
void Divide(){

    using namespace std;
    gStyle->SetOptStat(0);
    
    vector<TString> samples = {"Data","TTbar","ST","WJets"};
    // vector<TString> samples = {"Data"};

    for (TString sample : samples){

        TString rootFileName = "uhh2.AnalysisModuleRunner.MC."+sample+".root";
        if (sample=="Data") rootFileName.ReplaceAll(".MC.",".DATA.");

        TFile * inFile = new TFile (rootFileName);

        TH1F * h_pre  = (TH1F*) inFile->GetObjectChecked("NoCuts/PrimaryVertex","TH1F");
        TH1F * h_post = (TH1F*) inFile->GetObjectChecked("AfterCuts_1/PrimaryVertex","TH1F");
        
        TH1F * h_ratio = (TH1F*) h_post->Clone("h_ratio");

        float x_min = h_pre->GetBinCenter(1);
        float x_max = h_pre->GetBinCenter(h_pre->GetNbinsX());
        float y_flat = h_post->Integral()/h_pre->Integral();

        TLine * line = new TLine(x_min,y_flat,x_max,y_flat);
        line->SetLineColor(kRed);

        TCanvas * c = new TCanvas ("c","c");

        h_ratio->SetTitle("eff vs PU - "+sample+"; n. PV; after/pre cuts ");

        h_ratio->Divide(h_pre);
        h_ratio->Draw();
        line->Draw("same");

        c->Print("ratio_"+sample+".png","png");
        c->Print("ratio_"+sample+".pdf","pdf");
        
        delete c;
        delete h_ratio;
        delete h_pre;
        delete h_post;
        delete inFile;


    }




    gApplication->Terminate();

    return;
    
}
