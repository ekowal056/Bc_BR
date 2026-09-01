using namespace RooFit;

void make1DJpsiMuCorMFit()
{
    
    // Load in Data
    TFile *mcdata = new TFile("Bc2JpsiMu_fake_data.root", "Read");
    TTree *mctree;
    mctree=dynamic_cast<TTree*>(mcdata->Get("DecayTree"));

    double Bc_M, Bc_P, Bc_DIRA_OWNPV;
    mctree->SetBranchAddress("Bc_M", &Bc_M);
    mctree->SetBranchAddress("Bc_P", &Bc_P);
    mctree->SetBranchAddress("Bc_DIRA_OWNPV", &Bc_DIRA_OWNPV);

    // Make RooRealVariables
    RooRealVar CormBc("Cor_Bc_M", "m_{B^+_c}", 5300, 10000);
    CormBc.setUnit("MeV");
    CormBc.setBins(100);

    RooDataSet *FakeData = new RooDataSet("FakeData", "2018 Monte Carlo Sim", RooArgList(CormBc));

    int n = mctree->GetEntries();
    double corrM;
    
    for(int i = 0; i < n; i++){
        mctree->GetEntry(i);

        corrM = sqrt(Bc_M*Bc_M +Bc_P*Bc_P*(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV)) + Bc_P*sqrt(1 - Bc_DIRA_OWNPV*Bc_DIRA_OWNPV);
	CormBc.setVal(corrM);
	FakeData->add(RooArgList(CormBc));
    }
	
    // Make the Keys PDF
    RooKeysPdf keys("keys", "Keys PDF", CormBc, *FakeData, RooKeysPdf::MirrorBoth);

    // Plot
    RooPlot *frame = CormBc.frame(Title("Jpsi Mu Corrected Mass Fit (Psi2sMu)"));

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

