using namespace RooFit;

void JpsiPi_Step3_Fit(){

	TFile *mcdata = new TFile("Bc2JpsiPi_step1_sim.root", "Read");
	TTree *mctree;
	mctree=dynamic_cast<TTree*>(mcdata->Get("DecayTree;5"));

	RooRealVar mBc("Bc_M", "m_{B^+_c}", 6150, 6500);
        mBc.setUnit("MeV");
        mBc.setBins(100);

	RooDataSet *mc = new RooDataSet("mc", "2018 Monte Carlo Sim", mctree, RooArgList(mBc));

	RooRealVar mu("mu", "#mu", 6300, 6100, 6400);
        RooRealVar sig("sig", "#sigma", 20, 1, 250);
        RooRealVar sigL("sigL", "#sigmaL", 20, 1, 250);
        RooRealVar alphaL("alphaL", "#alpha_L", 0.5, 0.5,5); // + alpha = tail on left side, - alpha = tail on right side
        RooRealVar nL("nL", "n_L", 2, 1, 100);

        RooRealVar alphaR("alphaR", "#alpha_R", -1.5, -5,0.5); // + alpha = tail on left side, - alpha = tail on right side
        RooRealVar nR("nR", "n_R", 2, 1, 100);
        RooRealVar sigR("sigR", "#sigmaR", 20, 1, 250);
        RooRealVar fracsig("fracsig", "Fraction of Signals", 0.7, 0,1);


	RooCBShape signalL("signalL", "Signal Crystal Ball Left", mBc, mu, sigL, alphaL, nL);
        RooCBShape signalR("signalR", "Signal Crystal Ball Right", mBc, mu, sigR, alphaR, nR);

	RooAddPdf signal("signal", "double cb signal", RooArgList(signalL, signalR), RooArgList(fracsig));

	signal.fitTo(*mc);

	RooPlot *mcframe = mBc.frame();
        mc->plotOn(mcframe);
        signal.plotOn(mcframe);
        RooHist *mcpulls=mcframe->pullHist();
        signal.plotOn(mcframe, Components("*signal"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
        signal.paramOn(mcframe);	

	TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
	c1->Divide(1,2);
        c1->cd (1);
        mcframe->Draw();

	
        c1->cd(2);
        mcpulls->Draw();
	

///////// Data Fit ///////////

	TFile *rdata = new TFile("Bc2JpsiPi_step2.root", "Read");
	TTree *rtree;
	rtree=dynamic_cast<TTree*>(rdata->Get("DecayTree"));
	
	RooRealVar MVA("Likelihood_Result", "DLL", -6, 2);

	RooDataSet *data = new RooDataSet("data", "2018 Run2 Data", rtree, RooArgList(mBc,MVA), "Likelihood_Result>0");

	// Background
	RooRealVar lambda("lambda", "#lambda", -0.001, -10,0.0);
	RooRealVar Nsig("Nsig", "Number of Signal Events", 100, 1, 1e6);
        RooRealVar Nbg("Nbg", "Number of Background Events", 15000, 1, 1e6);
	RooExponential expoBG("expoBG", "Exponential Background", mBc, lambda);

	// Fix Signal n's and alphas
	nL.setConstant(true);
	nR.setConstant(true);
	alphaL.setConstant(true);
	alphaR.setConstant(true);
	fracsig.setConstant(true);
	sigR.setConstant(true);
	sigL.setConstant(true);
	
	RooAddPdf model("model", "model", RooArgList(signal, expoBG), RooArgList(Nsig, Nbg));
	model.fitTo(*data);

	RooPlot *frame = mBc.frame();
        data->plotOn(frame);
        model.plotOn(frame);
        RooHist *pulls=frame->pullHist();
        model.plotOn(frame, Components("*expo*"), LineStyle(kDashed), LineColor(kRed));
	model.plotOn(frame, Components("sig*"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
        model.paramOn(frame);

        TCanvas *c2 = new TCanvas("c2", "c2", 480, 600);
        c2->Divide(1,2);
        c2->cd (1);
        frame->Draw();


        c2->cd(2);
        pulls->Draw();

	



}
