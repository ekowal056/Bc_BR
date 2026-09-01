////////////////////////////////////////////////
///
/// TMVA Background Elimination Step2 of JpsiPi Processing
///
///////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
 
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
 
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
 


{

// This loads the library
    TMVA::Tools::Instance();
   

 // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 1;
   // 
   // --- Boosted Decision Trees

   Use["BDT1"]             = 1; // uses Adaptive Boost
//   Use["BDT2"]             = 1; // uses Adaptive Boost
//   Use["BDT3"]             = 1; // uses Adaptive Boost


//   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 1;


   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "Bc2JpsiPi_TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weight_mlfiles in the directory weight_ml/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   
   //auto factory = std::make_unique<TMVA::Factory>(
   //   "TMVAClassification", outputFile.get(),
   //   "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
   auto dataloader_raii = std::make_unique<TMVA::DataLoader>("dataset");
   auto *dataloader = dataloader_raii.get();
   
   
   
   
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

///////// TMVA Variables ///////////////////////////////   
   dataloader->AddVariable( "(Bc_FD_OWNPV*10e-3*Bc_M/Bc_P/299792458.0)", "B_{c} Proper Time", "MeV^{-1}" );
   dataloader->AddVariable("Bc_ENDVERTEX_CHI2/Bc_ENDVERTEX_NDOF", "Chi^{2}_{vtx} / NDOF (B_{c})", "");
   dataloader->AddVariable("Bc_IPCHI2_OWNPV", "Chi^{2}_{IP} (B_{c})", "");
   dataloader->AddVariable("BachPi_IPCHI2_OWNPV", "Chi^{2}_{IP} (pi^{+}})", "");
   dataloader->AddVariable("((BachPi_PX*Jpsi_PX) + (BachPi_PY*Jpsi_PY))/ ( std::sqrt(BachPi_PX*BachPi_PX + BachPi_PY*BachPi_PY) * std::sqrt(Jpsi_PX*Jpsi_PX + Jpsi_PY*Jpsi_PY))", "cos(pi^{+}, Jpsi)", "");
/*
//////// Bc Spectators ///////////////////////////////////////
   factory->AddSpectator("Bc_M", "Bc Mass", "MeV");
   factory->AddSpectator("Bc_ENDVERTEX_CHI2", "Bc_ENDVERTEX_CHI2", "");
   factory->AddSpectator("Bc_ENDVERTEX_CHI2", "Bc_ENDVERTEX_CHI2", "");
   factory->AddSpectator("Bc_FD_OWNPV","Bc FD OWNPV","");
   factory->AddSpectator("Bc_P","Bc P","MeV");


//////// BachPi Spectators ////////////////////////////////
   factory->AddSpectator("BachPi_PT", "BachPi PT", "MeV");
   factory->AddSpectator("BachPi_TRACK_CHI2NDOF", "BachPi TRACK CHI2NDOF", "");
   factory->AddSpectator("BachPi_IPCHI2_OWNPV", "BachPi IPCHI2 OWNPV", "");
   factory->AddSpectator("BachPi_PIDK", "BachPi PIDK", "");

   factory->AddSpectator("BachPi_PX","BachPi PX","MeV");
   factory->AddSpectator("BachPi_PY","BachPi PY","MeV");
   factory->AddSpectator("BachPi_PZ","BachPi PZ","MeV");
   factory->AddSpectator("BachPi_P","BachPi P","MeV");


//////// Mu Spectators ///////////////////
   factory->AddSpectator("MuM_PIDmu", "MuM PIDmu", "");
   factory->AddSpectator("MuP_PIDmu", "MuP PIDmu", "");
   factory->AddSpectator("MuM_PT", "MuM PT", "MeV");
   factory->AddSpectator("MuP_PT","MuP PT", "MeV");
   factory->AddSpectator("MuM_TRACK_CHI2NDOF", "MuM TRACK CHI2NDOF", "");
   factory->AddSpectator("MuP_TRACK_CHI2NDOF", "MuP TRACK CHI2NDOF", "");
   factory->AddSpectator("MuM_IPCHI2_OWNPV", "MuM IPCHI2 OWNPV", "");
   factory->AddSpectator("MuP_IPCHI2_OWNPV", "MuP IPCHI2 OWNPV", "");

   factory->AddSpectator("MuM_PX","MuM PX","MeV");
   factory->AddSpectator("MuM_PY","MuM PY","MeV");
   factory->AddSpectator("MuM_PZ","MuM PZ","MeV");
   factory->AddSpectator("MuM_P","MuM P","MeV");
   factory->AddSpectator("MuP_PX","MuP PX","MeV");
   factory->AddSpectator("MuP_PY","MuP PY","MeV");
   factory->AddSpectator("MuP_PZ","MuP PZ","MeV");
   factory->AddSpectator("MuP_P","MuP P","MeV");


/////// Jpsi Spectators ////////////////
   factory->AddSpectator("Jpsi_M", "M(mu^+ mu^-))", "MeV");
   factory->AddSpectator("Jpsi_ENDVERTEX_CHI2", "Jpsi ENDVERTEX CHI2","");
   factory->AddSpectator("Jpsi_ENDVERTEX_NDOF", "Jpsi ENDVERTEX NDOF", "");
   factory->AddSpectator("Jpsi_FDCHI2_OWNPV", "Jpsi FDCHI2 OWNPV", "");
   factory->AddSpectator("Jpsi_PT", "Jpsi PT","MeV");
   factory->AddSpectator("Jpsi_PX","Jpsi PX","MeV");
   factory->AddSpectator("Jpsi_PY","Jpsi PY","MeV");

////// Trigger Spectators ////////////////////////////
   factory->AddSpectator("Jpsi_L0MuonDecision_TOS", "Jpsi L0MuonDecision TOS", "");
   factory->AddSpectator("Jpsi_L0DiMuonDecision_TOS", "Jpsi L0DiMuonDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt1TrackMVADecision_TOS", "Jpsi Hlt1TrackMVADecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt1TrackMuonDecision_TOS", "Jpsi Hlt1TrackMuonDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt1DiMuonHighMassDecision_TOS", "Jpsi Hlt1DiMuonHighMassDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt2DiMuonDetachedJPsiDecision_TOS", "Jpsi Hlt2DiMuonDetachedJPsiDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt2DiMuonDetachedHeavyDecision_TOS", "Jpsi Hlt2DiMuonDetachedHeavyDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt2TopoMu2BodyDecision_TOS", "Jpsi Hlt2TopoMu2BodyDecision TOS", "");
   factory->AddSpectator("Jpsi_Hlt2TopoMu3BodyDecision_TOS", "Jpsi Hlt2TopoMu3BodyDecision TOS", "");

*/
   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TString sname = "Bc2JpsiPi_step1_sim.root";
   TString bname = "Bc2JpsiPi_step1_data_BKG.root";
//   TString fname = "./tmva_class_example.root";
   
//   if (gSystem->AccessPathName( fname ))  // file does not exist in local directory
//      gSystem->Exec("curl -O http://root.cern.ch/files/tmva_class_example.root");
   
   TFile *sinput = TFile::Open( sname );
   TFile *binput = TFile::Open( bname );
   
   std::cout << "--- TMVAClassification       : Using signal, background input files: " << sinput->GetName() << ", " << binput->GetName() << std::endl;
   
   // --- Register the training and test trees

   TTree *signal     = (TTree*)sinput->Get("DecayTree");
   TTree *background = (TTree*)binput->Get("DecayTree");
   
   // global event weight_mls per tree (see below for setting event-wise weight_mls)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

//   Double_t weight_ml;
//   signal->SetBranchAddress("weight_ml",&weight_ml);
  
   
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signal,     signalWeight     );
   dataloader->AddBackgroundTree( background, backgroundWeight );
// factory->SetSignalWeightExpression("weight_ml"); 
   factory->SetWeightExpression("weight_ml","Signal");
   factory->SetWeightExpression("1","Background");

   // To give different trees for training and testing, do as follows:
   //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   //
   //     // --- begin ----------------------------------------------------------
   //     std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   //     Float_t  treevars[4], weight_ml;
   //     
   //     // Signal
   //     for (UInt_t ivar=0; ivar<4; ivar++) signal->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<signal->GetEntries(); i++) {
   //        signal->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight_ml can also be event-wise
   //        if (i < signal->GetEntries()/2.0) factory->AddSignalTrainingEvent( vars, signalWeight );
   //        else                              factory->AddSignalTestEvent    ( vars, signalWeight );
   //     }
   //   
   //     // Background (has event weight_mls)
   //     background->SetBranchAddress( "weight_ml", &weight_ml );
   //     for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<background->GetEntries(); i++) {
   //        background->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight_ml can also be event-wise
   //        if (i < background->GetEntries()/2) factory->AddBackgroundTrainingEvent( vars, backgroundWeight*weight_ml );
   //        else                                factory->AddBackgroundTestEvent    ( vars, backgroundWeight*weight_ml );
   //     }
         // --- end ------------------------------------------------------------
   //
   // --- end of tree registration 

   // Set individual event weight_mls (the variables must exist in the original TTree)
   //    for signal    : factory->SetSignalWeightExpression    ("weight_ml1*weight_ml2");
   //    for background: factory->SetBackgroundWeightExpression("weight_ml1*weight_ml2");
//   factory->SetBackgroundWeightExpression( "weight_ml" );

   // Apply additional cuts on the signal and background samples (can be different)
//   TCut mycuts = "Bu_VTXISONUMVTX < 5 && Bu_MTDOCACHI2<9 && Ku_ProbNNk > 0.5 && Bu_BKGCAT == 0 && eventNumber%2 == 1"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
//   TCut mycutb = "Bu_MM > 5700 && Bu_VTXISONUMVTX < 5 && Bu_MTDOCACHI2<9 && Ku_ProbNNk > 0.5 && eventNumber%2 == 1"; // for example: TCut mycutb = "abs(var1)<0.5";
   TCut mycuts = "(Bc_M > 5800) && (Bc < 6800)";
   TCut mycutb = "((Bc_M < 5800) && (Bc_M > 5350)) || ((Bc_M < 6800) && (Bc_M > 8500 ))";
   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable


//   if (Use["BDT3"])  // Adaptive Boost
//      factory->BookMethod( TMVA::Types::kBDT, "BDT3",
//                           "!H:!V:NTrees=1200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:!UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=800:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:!UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDT1"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT1",
                           "!H:!V:NTrees=800:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:!UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=100" );

   if (Use["BDT2"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT2",
                           "!H:!V:NTrees=1600:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:!UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDT3"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT3",
                           "!H:!V:NTrees=1600:MinNodeSize=5%:MaxDepth=3:BoostType=Grad:AdaBoostBeta=0.5:!UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["MLP"])
      factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=sigmoid:VarTransform=N:NCycles=500:HiddenLayers=N:TestRate=10:!UseRegulator" );
/*
   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", 
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   / TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (Use["MLPBFGS"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTB"]) // Bagging
      factory->BookMethod( TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
*/
   // For an example of the category classifier usage, see: TMVAClassificationCategory

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // ---- STILL EXPERIMENTAL and only implemented for BDT's ! 
   // factory->OptimizeAllMethods("SigEffAt001","Scan");
//    factory->OptimizeAllMethods("ROCIntegral","FitGA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;



   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVAGui( outfileName );







}
