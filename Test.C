////////////
///
/// RooFit Code To Fit The Bc+ data
///
///

using namespace RooFit;


void Test(){

	/// Load in Data
	TChain *mctree = new TChain("TupleBcplus2JpsiPiplus/DecayTree");

	mctree->Add("NewTry/FullFilteredSim/*/Bc2Jpsipi_ANA2013-069_allsim.root");

	/// Define Mass Variable and Parameters
	RooRealVar mBc("Bc_MM", "m_{B^+_c}", 6150, 6500);
	mBc.setUnit("MeV");
	mBc.setBins(100);

	
//////////  Define Cut Variables ///////////////
	
	/// Trigger
	
	RooDataSet *mc = new RooDataSet("mc", "2018 Monte Carlo Sim", mctree, RooArgList(mBc));
	RooRealVar mu("mu", "#mu", 6300, 6100, 6400);
	RooRealVar sig("sig", "#sigma", 20, 1, 250);
	RooGaussian sig_g("sig_g", "Signal Gaussian", mBc, mu, sig);


	//sig_g.fitTo(*mc);

	RooPlot *mframe = mBc.frame();
	mc->plotOn(mframe); // PLot the Data on plot
        //sig_g.plotOn(mframe);
        //RooHist *pulls=mframe->pullHist(); //Grabs from the last two things plotted

        // Style and Decoration Fun!
        //model.plotOn(mframe, Components("*expo*"), LineStyle(kDashed), LineColor(kRed));
        //model.plotOn(mframe, Components("*sig*"), FillColor(kViolet), FillStyle(3001), DrawOption("F"));
        //sig_g.paramOn(mframe);

	TCanvas *c1 = new TCanvas("c1", "c1", 480, 600);
        //c1->Divide(1,2);
        //c1->cd(1);
        mframe->Draw(); //Draw the plot

        //c1->cd(2);

        //pulls->Draw();

        ///////////// 


}



