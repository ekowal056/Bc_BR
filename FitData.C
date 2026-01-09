////////////
///
/// RooFit Code To Fit The Bc+ data
///
///

using namespace RooFit;


void FitData(){

	/// Load in Data
//	TChain *mctree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");
	TChain *rtree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");

//	mctree->Add("NewTry/FullFilteredSim/*/Bc2Jpsipi_ANA2013-069_allsim.root");
	rtree->Add("FullFilters_Data/*/Bc2Jpsipi_ANA2013-069_alldata.root");

	/// Define Mass Variable and Parameters
	RooRealVar mBc("Bc_MM", "m_{B^+_c}", 6100, 6450);
	mBc.setUnit("MeV");
	mBc.setBins(100);

	
//////////  Define Cut Variables ///////////////
	
	/// Trigger
	RooRealVar Jpsi_L0MuonDecision_TOS("Jpsi_L0MuonDecision_TOS", "Jpsi L0MuonDecision TOS", 0, 1);
	RooRealVar Jpsi_L0DiMuonDecision_TOS("Jpsi_L0DiMuonDecision_TOS", "Jpsi L0DiMuonDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1TrackMVADecision_TOS("Jpsi_Hlt1TrackMVADecision_TOS", "Jpsi Hlt1TrackMVADecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1TrackMuonDecision_TOS("Jpsi_Hlt1TrackMuonDecision_TOS", "Jpsi Hlt1TrackMuonDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt1DiMuonHighMassDecision_TOS("Jpsi_Hlt1DiMuonHighMassDecision_TOS", "Jpsi Hlt1DiMuonHighMassDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", "Jpsi Hlt2DiMuonDetachedJPsiDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", "Jpsi Hlt2DiMuonDetachedHeavyDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2TopoMu2BodyDecision_TOS("Jpsi_Hlt2TopoMu2BodyDecision_TOS", "Jpsi Hlt2TopoMu2BodyDecision TOS", 0, 1);
	RooRealVar Jpsi_Hlt2TopoMu3BodyDecision_TOS("Jpsi_Hlt2TopoMu3BodyDecision_TOS", "Jpsi Hlt2TopoMu3BodyDecision TOS", 0, 1);

	/// MC Truth Cut Variables
	RooRealVar Bc_TRUEID("Bc_TRUEID", "Bc TRUEID", 0, 500);
	RooRealVar Jpsi_TRUEID("Jpsi_TRUEID", "Jpsi TRUEID", 0, 450);
	RooRealVar Bc_BKGCAT("Bc_BKGCAT", "Bc BKGCAT", 0, 130);
	RooRealVar Jpsi_BKGCAT("Jpsi_BKGCAT", "Jpsi BKGCAT", 0, 130);
	RooRealVar BachPi_isMuon("BachPi_isMuon", "BachPi isMuon", 0, 1);

	/// Main Cuts
	//rooRealVar ("", "", , );


////////// Create RooDataSets //////////////////
	
	//RooDataSet *mc = new RooDataSet("mc", "2018 Monte Carlo Sim", mctree, RooArgList(Jpsi_L0MuonDecision_TOS,Jpsi_L0DiMuonDecision_TOS, Jpsi_Hlt1TrackMVADecision_TOS,Jpsi_Hlt1TrackMuonDecision_TOS,Jpsi_Hlt1DiMuonHighMassDecision_TOS,Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS,Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS,Jpsi_Hlt2TopoMu2BodyDecision_TOS,Jpsi_Hlt2TopoMu3BodyDecision_TOS,Bc_TRUEID,Jpsi_TRUEID,Jpsi_BKGCAT,Bc_BKGCAT,BachPi_isMuon), 
//			"(Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)" 
//			"&& (( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1) || Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)" 
//			"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1) || (Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))"
//			"&& (TMath::Abs(Bc_TRUEID) == 541 && TMath::Abs(Jpsi_TRUEID) == 443)"
//			"&& ((Jpsi_BKGCAT == 0 && Bc_BKGCAT == 0) || (Jpsi_BKGCAT == 50 && Bc_BKGCAT == 50))"
//			"&& (BachPi_isMuon == 0)"
//			//"&& "
//
//		
//		);

	RooDataSet *data = new RooDataSet("data", "2018 Run2 Data", rtree, RooArgList(Jpsi_L0MuonDecision_TOS,Jpsi_L0DiMuonDecision_TOS, Jpsi_Hlt1TrackMVADecision_TOS,Jpsi_Hlt1TrackMuonDecision_TOS,Jpsi_Hlt1DiMuonHighMassDecision_TOS,Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS,Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS,Jpsi_Hlt2TopoMu2BodyDecision_TOS,Jpsi_Hlt2TopoMu3BodyDecision_TOS), 
			"(Jpsi_L0MuonDecision_TOS==1 || Jpsi_L0DiMuonDecision_TOS==1)"
                	"&& (( Jpsi_Hlt1TrackMVADecision_TOS==1|| Jpsi_Hlt1TrackMuonDecision_TOS==1) || Jpsi_Hlt1DiMuonHighMassDecision_TOS==1)"
                	"&& (( Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS==1 || Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS==1) || (Jpsi_Hlt2TopoMu2BodyDecision_TOS==1|| Jpsi_Hlt2TopoMu3BodyDecision_TOS==1))"
		 
		);



///////////// Create Fit Variables and Shape ///////////////////

	RooRealVar mu("mu", "#mu", 6300, 6100, 6400);
	RooRealVar sig("sig", "#sigma", 20, 1, 250);
	RooRealVar lambda("lambda", "#lambda", -0.001, -10,0.0);
	RooRealVar frac("frac", "fraction of Signal vs Background", 0, 1);

	RooGaussian sig_g("sig_g", "Signal Gaussian", mBc, mu, sig);
	RooExponential expoBG("expoBG", "Exponential Background", mBc, lambda);

	RooAddPdf model("model", "model", RooArgList(sig_g, expoBG), RooArgList(frac));

	model.fitTo(*data);

	RooPlot *mframe = mBc.frame();
	data->plotOn(mframe); // PLot the Data on plot
        model.plotOn(mframe);
        RooHist *pulls=mframe->pullHist(); //Grabs from the last two things plotted

        // Style and Decoration Fun!
        model.plotOn(mframe, Components("*expo*"), LineStyle(kDashed), LineColor(kRed));
        model.plotOn(mframe, Components("*sig*"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
        model.paramOn(mframe);

	TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
        c1->Divide(1,2);
        c1->cd(1);
        mframe->Draw(); //Draw the plot

        c1->cd(2);

        pulls->Draw();

        ///////////// 

        // Define a Range
        //mBc.setRange("sigrange", 5220, 5340); // Just an internal property of mB so does not need a nice name
        //RooAbsReal *intBG = expoBG.createIntegral(RooArgSet(mBc), NormSet(mBc), Range("sigrange"));

	//cout << "\n ##################### \n BG integral is " << Nbg.getVal()*intBG->getVal() << "+/-" << Nbg.getError()*intBG->getVal() << endl;









}



