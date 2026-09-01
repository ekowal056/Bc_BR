using namespace RooFit;

void make1DJpsiMuVisMFit()
{
    
    // Load in Data
    TFile *mcdata = new TFile("Bc2JpsiMu_fake_data.root", "Read");
    TTree *mctree;
    mctree=dynamic_cast<TTree*>(mcdata->Get("DecayTree"));


    // Make RooRealVariables
    RooRealVar mBc("Bc_M", "m_{B^+_c}", 5300, 6500);
    mBc.setUnit("MeV");
    mBc.setBins(100);

    RooDataSet *FakeData = new RooDataSet("FakeData", "2018 Monte Carlo Sim", mctree, RooArgList(mBc));

	
    // Make the Keys PDF
    RooKeysPdf keys("keys", "Keys PDF", mBc, *FakeData, RooKeysPdf::MirrorBoth);

    // Plot
    RooPlot *frame = mBc.frame(Title("Jpsi Mu Visible Mass Fit (Psi2sMu)"));

    FakeData->plotOn(frame);
    keys.plotOn(frame);
    RooHist *pulls=frame->pullHist();

    TCanvas* c = new TCanvas("c", "RooKeyFit", 480, 600);
    c->Divide(1,2);
    c->cd (1);
    frame->Draw();

    c->cd(2);
    pulls->Draw();
    //c->SaveAs("JpsiMu_Psis2_VisMFit.png");
}

