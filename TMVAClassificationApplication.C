/////////
////
///
///
///
///
///



#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
 
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
 
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
 
using namespace TMVA;
 
void TMVAClassificationApplication( TString myMethodList = "" )
{
 
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();
 
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
 
   // Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 0; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   Use["DNN_CPU"] = 0;         // CUDA-accelerated DNN training.
   Use["DNN_GPU"] = 0;         // Multi-core accelerated DNN.
   //
   // Support Vector Machine
   Use["SVM"]             = 0;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 0; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------
   Use["Plugin"]          = 0;
   Use["Category"]        = 0;
   Use["SVM_Gauss"]       = 0;
   Use["SVM_Poly"]        = 0;
   Use["SVM_Lin"]         = 0;
 
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;
 
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
 
      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);
 
         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }
 
   // --------------------------------------------------------------------------------------------------
 
   // Create the Reader object
 
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
 
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   
   // Define variables : idk which ones
   Float_t Bc_ProperTime, Bc_ENDVERTEX_CHI2_NDOF, Log_Bc_IPCHI2, Log_BachPi_IPCHI2, Cos_BachPi_Jpsi;

   reader->AddVariable( "Bc_ProperTime := (Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)", &Bc_ProperTime);
   reader->AddVariable("Bc_ENDVERTEX_CHI2_NDOF := Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF", &Bc_ENDVERTEX_CHI2_NDOF);
   reader->AddVariable("Log_Bc_IPCHI2 := log(Bc_IPCHI2_OWNPV)", &Log_Bc_IPCHI2);
   reader->AddVariable("Log_BachPi_IPCHI2 := log(BachPi_IPCHI2_OWNPV)", &Log_BachPi_IPCHI2);
   reader->AddVariable("Cos_BachPi_Jpsi := ((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY))", &Cos_BachPi_Jpsi);
   
   //reader->AddVariable( "myvar1 := var1+var2", &var1 );
   //reader->AddVariable( "var3",                &var3 );
 
   // Spectator variables declared in the training have to be added to the reader, too
   //Float_t spec1,spec2;
   //reader->AddSpectator( "spec1 := var1*2",   &spec1 );
   //reader->AddSpectator( "spec2 := var1*3",   &spec2 );
 
/*
////////// Bc Spectators ///////////////////////////////////

//////// BachPi Spectators ////////////////////////////////
   Float_t BachPi_PT, BachPi_TRACK_CHI2NDOF, BachPi_PIDK, BachPi_PZ, BachPi_P;
   reader->AddSpectator("BachPi_PT", &BachPi_PT);
   reader->AddSpectator("BachPi_TRACK_CHI2NDOF", &BachPi_TRACK_CHI2NDOF);
   reader->AddSpectator("BachPi_PIDK", &BachPi_PIDK);

   reader->AddSpectator("BachPi_PZ", &BachPi_PZ);
   reader->AddSpectator("BachPi_P", &BachPi_P);

//////// Mu Spectators ///////////////////
   Float_t MuM_PIDmu, MuP_PIDmu, MuM_PT, MuP_PT, MuM_TRACK_CHI2NDOF, MuP_TRACK_CHI2NDOF, MuM_IPCHI2_OWNPV, MuP_IPCHI2_OWNPV, MuM_PX, MuM_PY, MuM_PZ, MuM_P, MuP_PX, MuP_PY, MuP_PZ, MuP_P;
   reader->AddSpectator("MuM_PIDmu",&MuM_PIDmu);
   reader->AddSpectator("MuP_PIDmu",&MuP_PIDmu);
   reader->AddSpectator("MuM_PT",&MuM_PT);
   reader->AddSpectator("MuP_PT",&MuP_PT);
   reader->AddSpectator("MuM_TRACK_CHI2NDOF", &MuM_TRACK_CHI2NDOF);
   reader->AddSpectator("MuP_TRACK_CHI2NDOF", &MuP_TRACK_CHI2NDOF);
   reader->AddSpectator("MuM_IPCHI2_OWNPV", &MuM_IPCHI2_OWNPV);
   reader->AddSpectator("MuP_IPCHI2_OWNPV", &MuP_IPCHI2_OWNPV);

   reader->AddSpectator("MuM_PX", &MuM_PX);
   reader->AddSpectator("MuM_PY", &MuM_PY);
   reader->AddSpectator("MuM_PZ", &MuM_PZ);
   reader->AddSpectator("MuM_P", &MuM_P);
   reader->AddSpectator("MuP_PX",&MuP_PX);
   reader->AddSpectator("MuP_PY",&MuP_PY);
   reader->AddSpectator("MuP_PZ",&MuP_PZ);
   reader->AddSpectator("MuP_P",&MuP_P);

/////// Jpsi Spectators ////////////////
   Float_t Jpsi_M, Jpsi_ENDVERTEX_CHI2, Jpsi_ENDVERTEX_NDOF, Jpsi_FDCHI2_OWNPV, Jpsi_PT;
   reader->AddSpectator("Jpsi_M", &Jpsi_M);
   reader->AddSpectator("Jpsi_ENDVERTEX_CHI2", &Jpsi_ENDVERTEX_CHI2);
   reader->AddSpectator("Jpsi_ENDVERTEX_NDOF", &Jpsi_ENDVERTEX_NDOF);
   reader->AddSpectator("Jpsi_FDCHI2_OWNPV",&Jpsi_FDCHI2_OWNPV );
   reader->AddSpectator("Jpsi_PT",&Jpsi_PT);

////// Trigger Spectators ////////////////////////////
   Float_t Jpsi_L0MuonDecision_TOS, Jpsi_L0DiMuonDecision_TOS, Jpsi_Hlt1TrackMVADecision_TOS, Jpsi_Hlt1TrackMuonDecision_TOS, Jpsi_Hlt1DiMuonHighMassDecision_TOS, Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS, Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS, Jpsi_Hlt2TopoMu2BodyDecision_TOS, Jpsi_Hlt2TopoMu3BodyDecision_TOS;
   reader->AddSpectator("Jpsi_L0MuonDecision_TOS", &Jpsi_L0MuonDecision_TOS);
   reader->AddSpectator("Jpsi_L0DiMuonDecision_TOS", &Jpsi_L0DiMuonDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt1TrackMVADecision_TOS", &Jpsi_Hlt1TrackMVADecision_TOS);
   reader->AddSpectator("Jpsi_Hlt1TrackMuonDecision_TOS", &Jpsi_Hlt1TrackMuonDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt1DiMuonHighMassDecision_TOS", &Jpsi_Hlt1DiMuonHighMassDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", &Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS",&Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt2TopoMu2BodyDecision_TOS",&Jpsi_Hlt2TopoMu2BodyDecision_TOS);
   reader->AddSpectator("Jpsi_Hlt2TopoMu3BodyDecision_TOS",&Jpsi_Hlt2TopoMu3BodyDecision_TOS);
*/

   //Float_t Category_cat1, Category_cat2, Category_cat3;
   //if (Use["Category"]){
      // Add artificial spectators for distinguishing categories
  //    reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
   //   reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
   //   reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
   //}
 
   // Book the MVA methods
 
   TString dir    = "dataset/weights/";
   TString prefix = "TMVAClassification";
 
   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName, weightfile );
      }
   }
 
   // Book output histograms
   UInt_t nbin = 100;
   TH1F *histLk(0);
   TH1F *histLkD(0);
   TH1F *histLkPCA(0);
   TH1F *histLkKDE(0);
   TH1F *histLkMIX(0);
   TH1F *histPD(0);
   TH1F *histPDD(0);
   TH1F *histPDPCA(0);
   TH1F *histPDEFoam(0);
   TH1F *histPDEFoamErr(0);
   TH1F *histPDEFoamSig(0);
   TH1F *histKNN(0);
   TH1F *histHm(0);
   TH1F *histFi(0);
   TH1F *histFiG(0);
   TH1F *histFiB(0);
   TH1F *histLD(0);
   TH1F *histNn(0);
   TH1F *histNnbfgs(0);
   TH1F *histNnbnn(0);
   TH1F *histNnC(0);
   TH1F *histNnT(0);
   TH1F *histBdt(0);
   TH1F *histBdtG(0);
   TH1F *histBdtB(0);
   TH1F *histBdtD(0);
   TH1F *histBdtF(0);
   TH1F *histRf(0);
   TH1F *histSVMG(0);
   TH1F *histSVMP(0);
   TH1F *histSVML(0);
   TH1F *histFDAMT(0);
   TH1F *histFDAGA(0);
   TH1F *histCat(0);
   TH1F *histPBdt(0);
   TH1F *histDnnGpu(0);
   TH1F *histDnnCpu(0);
 
   if (Use["Likelihood"])    histLk      = new TH1F( "MVA_Likelihood",    "MVA_Likelihood",    nbin, -1, 1 );
   if (Use["LikelihoodD"])   histLkD     = new TH1F( "MVA_LikelihoodD",   "MVA_LikelihoodD",   nbin, -1, 0.9999 );
   if (Use["LikelihoodPCA"]) histLkPCA   = new TH1F( "MVA_LikelihoodPCA", "MVA_LikelihoodPCA", nbin, -1, 1 );
   if (Use["LikelihoodKDE"]) histLkKDE   = new TH1F( "MVA_LikelihoodKDE", "MVA_LikelihoodKDE", nbin,  -0.00001, 0.99999 );
   if (Use["LikelihoodMIX"]) histLkMIX   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin,  0, 1 );
   if (Use["PDERS"])         histPD      = new TH1F( "MVA_PDERS",         "MVA_PDERS",         nbin,  0, 1 );
   if (Use["PDERSD"])        histPDD     = new TH1F( "MVA_PDERSD",        "MVA_PDERSD",        nbin,  0, 1 );
   if (Use["PDERSPCA"])      histPDPCA   = new TH1F( "MVA_PDERSPCA",      "MVA_PDERSPCA",      nbin,  0, 1 );
   if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
   if (Use["HMatrix"])       histHm      = new TH1F( "MVA_HMatrix",       "MVA_HMatrix",       nbin, -0.95, 1.55 );
   if (Use["Fisher"])        histFi      = new TH1F( "MVA_Fisher",        "MVA_Fisher",        nbin, -4, 4 );
   if (Use["FisherG"])       histFiG     = new TH1F( "MVA_FisherG",       "MVA_FisherG",       nbin, -1, 1 );
   if (Use["BoostedFisher"]) histFiB     = new TH1F( "MVA_BoostedFisher", "MVA_BoostedFisher", nbin, -2, 2 );
   if (Use["LD"])            histLD      = new TH1F( "MVA_LD",            "MVA_LD",            nbin, -2, 2 );
   if (Use["MLP"])           histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, -1.25, 1.5 );
   if (Use["MLPBFGS"])       histNnbfgs  = new TH1F( "MVA_MLPBFGS",       "MVA_MLPBFGS",       nbin, -1.25, 1.5 );
   if (Use["MLPBNN"])        histNnbnn   = new TH1F( "MVA_MLPBNN",        "MVA_MLPBNN",        nbin, -1.25, 1.5 );
   if (Use["CFMlpANN"])      histNnC     = new TH1F( "MVA_CFMlpANN",      "MVA_CFMlpANN",      nbin,  0, 1 );
   if (Use["TMlpANN"])       histNnT     = new TH1F( "MVA_TMlpANN",       "MVA_TMlpANN",       nbin, -1.3, 1.3 );
   if (Use["DNN_GPU"]) histDnnGpu = new TH1F("MVA_DNN_GPU", "MVA_DNN_GPU", nbin, -0.1, 1.1);
   if (Use["DNN_CPU"]) histDnnCpu = new TH1F("MVA_DNN_CPU", "MVA_DNN_CPU", nbin, -0.1, 1.1);
   if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );
   if (Use["BDTG"])          histBdtG    = new TH1F( "MVA_BDTG",          "MVA_BDTG",          nbin, -1.0, 1.0 );
   if (Use["BDTB"])          histBdtB    = new TH1F( "MVA_BDTB",          "MVA_BDTB",          nbin, -1.0, 1.0 );
   if (Use["BDTD"])          histBdtD    = new TH1F( "MVA_BDTD",          "MVA_BDTD",          nbin, -0.8, 0.8 );
   if (Use["BDTF"])          histBdtF    = new TH1F( "MVA_BDTF",          "MVA_BDTF",          nbin, -1.0, 1.0 );
   if (Use["RuleFit"])       histRf      = new TH1F( "MVA_RuleFit",       "MVA_RuleFit",       nbin, -2.0, 2.0 );
   if (Use["SVM_Gauss"])     histSVMG    = new TH1F( "MVA_SVM_Gauss",     "MVA_SVM_Gauss",     nbin,  0.0, 1.0 );
   if (Use["SVM_Poly"])      histSVMP    = new TH1F( "MVA_SVM_Poly",      "MVA_SVM_Poly",      nbin,  0.0, 1.0 );
   if (Use["SVM_Lin"])       histSVML    = new TH1F( "MVA_SVM_Lin",       "MVA_SVM_Lin",       nbin,  0.0, 1.0 );
   if (Use["FDA_MT"])        histFDAMT   = new TH1F( "MVA_FDA_MT",        "MVA_FDA_MT",        nbin, -2.0, 3.0 );
   if (Use["FDA_GA"])        histFDAGA   = new TH1F( "MVA_FDA_GA",        "MVA_FDA_GA",        nbin, -2.0, 3.0 );
   if (Use["Category"])      histCat     = new TH1F( "MVA_Category",      "MVA_Category",      nbin, -2., 2. );
   if (Use["Plugin"])        histPBdt    = new TH1F( "MVA_PBDT",          "MVA_BDT",           nbin, -0.8, 0.8 );
 
   // PDEFoam also returns per-event error, fill in histogram, and also fill significance
   if (Use["PDEFoam"]) {
      histPDEFoam    = new TH1F( "MVA_PDEFoam",       "MVA_PDEFoam",              nbin,  0, 1 );
      histPDEFoamErr = new TH1F( "MVA_PDEFoamErr",    "MVA_PDEFoam error",        nbin,  0, 1 );
      histPDEFoamSig = new TH1F( "MVA_PDEFoamSig",    "MVA_PDEFoam significance", nbin,  0, 10 );
   }
 
   // Book example histogram for probability (the other methods are done similarly)
   TH1F *probHistFi(0), *rarityHistFi(0);
   if (Use["Fisher"]) {
      probHistFi   = new TH1F( "MVA_Fisher_Proba",  "MVA_Fisher_Proba",  nbin, 0, 1 );
      rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
   }
 
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   TFile *input(nullptr);
   TString fname = "Bc2JpsiPi_step1_data.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
 
   // Event loop
 
   // Prepare the event tree
   // - Here the variable names have to corresponds to your tree
   // - You can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   
   
   std::cout << "--- Select signal sample" << std::endl;
   TTree* theTree = (TTree*)input->Get("DecayTree");
   
   // Define inputs for all my calculated variables
   Double_t Bc_FD_OWNPV , Bc_M , Bc_P , Bc_ENDVERTEX_CHI2 , Bc_IPCHI2_OWNPV , BachPi_IPCHI2_OWNPV , BachPi_PX , Jpsi_PX , BachPi_PY , Jpsi_PY;
   Int_t Bc_ENDVERTEX_NDOF;

   theTree->SetBranchAddress( "Bc_FD_OWNPV", &Bc_FD_OWNPV );
   theTree->SetBranchAddress( "Bc_M", &Bc_M );
   theTree->SetBranchAddress( "Bc_P", &Bc_P );
   theTree->SetBranchAddress( "Bc_ENDVERTEX_CHI2", &Bc_ENDVERTEX_CHI2 );
   theTree->SetBranchAddress( "Bc_ENDVERTEX_NDOF", &Bc_ENDVERTEX_NDOF );
   theTree->SetBranchAddress( "Bc_IPCHI2_OWNPV", &Bc_IPCHI2_OWNPV );
   theTree->SetBranchAddress( "BachPi_IPCHI2_OWNPV", &BachPi_IPCHI2_OWNPV );
   theTree->SetBranchAddress( "BachPi_PX", &BachPi_PX );
   theTree->SetBranchAddress( "Jpsi_PX", &Jpsi_PX );
   theTree->SetBranchAddress( "BachPi_PY", &BachPi_PY );
   theTree->SetBranchAddress( "Jpsi_PY", &Jpsi_PY );


   //Define output TFile
   TString outfilename = "Bc2JpsiPi_step2.root";
   TFile *outfile = new TFile(outfilename, "RECREATE");
   TTree *outtree = theTree->CloneTree();
   
   TString OutputBranchName = "Likelihood_Result";
   Double_t signalresponse,Likeli;
   TBranch *br = outtree->Branch(OutputBranchName,&signalresponse);

   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;
 
   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests
 
   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
 
      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
 
      theTree->GetEntry(ievt);
 
      // Do the math!!!!!!!!!!!!!!!!!!!!!!!!
      Bc_ProperTime = (Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0);
      Bc_ENDVERTEX_CHI2_NDOF = Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF;
      Log_Bc_IPCHI2 = log(Bc_IPCHI2_OWNPV);
      Log_BachPi_IPCHI2 = log(BachPi_IPCHI2_OWNPV);
      Cos_BachPi_Jpsi = ((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY));

      // Return the MVA outputs and fill into histograms
 
      if (Use["CutsGA"]) {
         // Cuts is a special case: give the desired signal efficiency
         Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
         if (passed) nSelCutsGA++;
      }
 
      /// Maybe write out a copy of Tfile with new branch, that has the EvaluateMVA results instead of filling out a histogram
      if (Use["Likelihood"   ]){   
	      Likeli = reader->EvaluateMVA( "Likelihood method");
	      signalresponse = Likeli;
	      histLk->Fill(Likeli );
              br->Fill();
      };
      	      
      if (Use["LikelihoodD"  ])   histLkD    ->Fill( reader->EvaluateMVA( "LikelihoodD method"   ) );
      if (Use["LikelihoodPCA"])   histLkPCA  ->Fill( reader->EvaluateMVA( "LikelihoodPCA method" ) );
      if (Use["LikelihoodKDE"])   histLkKDE  ->Fill( reader->EvaluateMVA( "LikelihoodKDE method" ) );
      if (Use["LikelihoodMIX"])   histLkMIX  ->Fill( reader->EvaluateMVA( "LikelihoodMIX method" ) );
      if (Use["PDERS"        ])   histPD     ->Fill( reader->EvaluateMVA( "PDERS method"         ) );
      if (Use["PDERSD"       ])   histPDD    ->Fill( reader->EvaluateMVA( "PDERSD method"        ) );
      if (Use["PDERSPCA"     ])   histPDPCA  ->Fill( reader->EvaluateMVA( "PDERSPCA method"      ) );
      if (Use["KNN"          ])   histKNN    ->Fill( reader->EvaluateMVA( "KNN method"           ) );
      if (Use["HMatrix"      ])   histHm     ->Fill( reader->EvaluateMVA( "HMatrix method"       ) );
      if (Use["Fisher"       ])   histFi     ->Fill( reader->EvaluateMVA( "Fisher method"        ) );
      if (Use["FisherG"      ])   histFiG    ->Fill( reader->EvaluateMVA( "FisherG method"       ) );
      if (Use["BoostedFisher"])   histFiB    ->Fill( reader->EvaluateMVA( "BoostedFisher method" ) );
      if (Use["LD"           ])   histLD     ->Fill( reader->EvaluateMVA( "LD method"            ) );
      if (Use["MLP"          ])   histNn     ->Fill( reader->EvaluateMVA( "MLP method"           ) );
      if (Use["MLPBFGS"      ])   histNnbfgs ->Fill( reader->EvaluateMVA( "MLPBFGS method"       ) );
      if (Use["MLPBNN"       ])   histNnbnn  ->Fill( reader->EvaluateMVA( "MLPBNN method"        ) );
      if (Use["CFMlpANN"     ])   histNnC    ->Fill( reader->EvaluateMVA( "CFMlpANN method"      ) );
      if (Use["TMlpANN"      ])   histNnT    ->Fill( reader->EvaluateMVA( "TMlpANN method"       ) );
      if (Use["DNN_GPU"]) histDnnGpu->Fill(reader->EvaluateMVA("DNN_GPU method"));
      if (Use["DNN_CPU"]) histDnnCpu->Fill(reader->EvaluateMVA("DNN_CPU method"));
      if (Use["BDT"          ])   histBdt    ->Fill( reader->EvaluateMVA( "BDT method"           ) );
      if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"          ) );
      if (Use["BDTB"         ])   histBdtB   ->Fill( reader->EvaluateMVA( "BDTB method"          ) );
      if (Use["BDTD"         ])   histBdtD   ->Fill( reader->EvaluateMVA( "BDTD method"          ) );
      if (Use["BDTF"         ])   histBdtF   ->Fill( reader->EvaluateMVA( "BDTF method"          ) );
      if (Use["RuleFit"      ])   histRf     ->Fill( reader->EvaluateMVA( "RuleFit method"       ) );
      if (Use["SVM_Gauss"    ])   histSVMG   ->Fill( reader->EvaluateMVA( "SVM_Gauss method"     ) );
      if (Use["SVM_Poly"     ])   histSVMP   ->Fill( reader->EvaluateMVA( "SVM_Poly method"      ) );
      if (Use["SVM_Lin"      ])   histSVML   ->Fill( reader->EvaluateMVA( "SVM_Lin method"       ) );
      if (Use["FDA_MT"       ])   histFDAMT  ->Fill( reader->EvaluateMVA( "FDA_MT method"        ) );
      if (Use["FDA_GA"       ])   histFDAGA  ->Fill( reader->EvaluateMVA( "FDA_GA method"        ) );
      if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );
      if (Use["Plugin"       ])   histPBdt   ->Fill( reader->EvaluateMVA( "P_BDT method"         ) );
 
      // Retrieve also per-event error
      if (Use["PDEFoam"]) {
         Double_t val = reader->EvaluateMVA( "PDEFoam method" );
         Double_t err = reader->GetMVAError();
         histPDEFoam   ->Fill( val );
         histPDEFoamErr->Fill( err );
         if (err>1.e-50) histPDEFoamSig->Fill( val/err );
      }
 
      // Retrieve probability instead of MVA output
      if (Use["Fisher"])   {
         probHistFi  ->Fill( reader->GetProba ( "Fisher method" ) );
         rarityHistFi->Fill( reader->GetRarity( "Fisher method" ) );
      }
   }
 
   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
 
   // Get efficiency for cuts classifier
   if (Use["CutsGA"]) std::cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
                                << " (for a required signal efficiency of " << effS << ")" << std::endl;
 
   if (Use["CutsGA"]) {
 
      // test: retrieve cuts for particular signal efficiency
      TMVA::MethodCuts* mcuts = dynamic_cast<TMVA::MethodCuts*>(reader->FindMVA( "CutsGA method" ));
 
      if (mcuts) {
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << std::endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
            std::cout << "... Cut: "
                      << cutsMin[ivar]
                      << " < \""
                      << mcuts->GetInputVar(ivar)
                      << "\" <= "
                      << cutsMax[ivar] << std::endl;
         }
         std::cout << "--- -------------------------------------------------------------" << std::endl;
      }
   }
 
   // Write histograms
 
   //TFile *target  = new TFile( "TMVApp.root","RECREATE" );
   if (Use["Likelihood"   ])   histLk     ->Write();
   if (Use["LikelihoodD"  ])   histLkD    ->Write();
   if (Use["LikelihoodPCA"])   histLkPCA  ->Write();
   if (Use["LikelihoodKDE"])   histLkKDE  ->Write();
   if (Use["LikelihoodMIX"])   histLkMIX  ->Write();
   if (Use["PDERS"        ])   histPD     ->Write();
   if (Use["PDERSD"       ])   histPDD    ->Write();
   if (Use["PDERSPCA"     ])   histPDPCA  ->Write();
   if (Use["KNN"          ])   histKNN    ->Write();
   if (Use["HMatrix"      ])   histHm     ->Write();
   if (Use["Fisher"       ])   histFi     ->Write();
   if (Use["FisherG"      ])   histFiG    ->Write();
   if (Use["BoostedFisher"])   histFiB    ->Write();
   if (Use["LD"           ])   histLD     ->Write();
   if (Use["MLP"          ])   histNn     ->Write();
   if (Use["MLPBFGS"      ])   histNnbfgs ->Write();
   if (Use["MLPBNN"       ])   histNnbnn  ->Write();
   if (Use["CFMlpANN"     ])   histNnC    ->Write();
   if (Use["TMlpANN"      ])   histNnT    ->Write();
   if (Use["DNN_GPU"]) histDnnGpu->Write();
   if (Use["DNN_CPU"]) histDnnCpu->Write();
   if (Use["BDT"          ])   histBdt    ->Write();
   if (Use["BDTG"         ])   histBdtG   ->Write();
   if (Use["BDTB"         ])   histBdtB   ->Write();
   if (Use["BDTD"         ])   histBdtD   ->Write();
   if (Use["BDTF"         ])   histBdtF   ->Write();
   if (Use["RuleFit"      ])   histRf     ->Write();
   if (Use["SVM_Gauss"    ])   histSVMG   ->Write();
   if (Use["SVM_Poly"     ])   histSVMP   ->Write();
   if (Use["SVM_Lin"      ])   histSVML   ->Write();
   if (Use["FDA_MT"       ])   histFDAMT  ->Write();
   if (Use["FDA_GA"       ])   histFDAGA  ->Write();
   if (Use["Category"     ])   histCat    ->Write();
   if (Use["Plugin"       ])   histPBdt   ->Write();
 
   // Write also error and significance histos
   if (Use["PDEFoam"]) { histPDEFoam->Write(); histPDEFoamErr->Write(); histPDEFoamSig->Write(); }
 
   // Write also probability hists
   if (Use["Fisher"]) { if (probHistFi != 0) probHistFi->Write(); if (rarityHistFi != 0) rarityHistFi->Write(); }
   //target->Close();
 
   outfile->Write();
   outfile->Close();
   std::cout << "--- Created root file:  " << outfilename  << "containing the MVA output histograms and new MVA results branch: " << OutputBranchName << std::endl;
 
   delete reader;
 
   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
}
 
int main( int argc, char** argv )
{
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVAClassificationApplication(methodList);
   return 0;
}


