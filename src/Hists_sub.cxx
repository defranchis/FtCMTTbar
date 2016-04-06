#include <memory>

#include "UHH2/FtCMTTbar/include/Hists_sub.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TopJetIds.h"
#include "TH1F.h"
#include <iostream>
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/Utils.h"


using namespace std;
using namespace uhh2;
using namespace uhh2examples;

Hists_sub::Hists_sub(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  //btag variables
  book<TH1F>("subCSV_b", "combined secondary vertex discriminator of the subjet", 100, 0., 1.);  
  book<TH1F>("subCSV_c", "combined secondary vertex discriminator of the subjet", 100, 0., 1.); 
  book<TH1F>("subCSV_uds", "combined secondary vertex discriminator of the subjet", 100, 0., 1.); 
  book<TH1F>("subCSV_g", "combined secondary vertex discriminator of the subjet", 100, 0., 1.); 
  book<TH1F>("subCSV_none", "combined secondary vertex discriminator of the subjet", 100, 0., 1.); 
  book<TH1F>("subCSV_data", "combined secondary vertex discriminator of the subjet", 100, 0., 1.);

  book<TH1F>("subFlavour_b", "matched flavour of the subjet", 4, 0., 4.);  
  book<TH1F>("subFlavour_c", "matched flavour of the subjet", 4, 0., 4.); 
  book<TH1F>("subFlavour_uds", "matched flavour of the subjet", 4, 0., 4.); 
  book<TH1F>("subFlavour_g", "matched flavour of the subjet", 4, 0., 4.); 
  book<TH1F>("subFlavour_none", "matched flavour of the subjet", 4, 0., 4.); 
  book<TH1F>("subFlavour_data", "matched flavour of the subjet", 4, 0., 4.);

  //track impact parameter tag info
  book<TH1F>("subTrackMomentum_b", "momentum of tracks in the subjet", 50, 0., 15.);  
  book<TH1F>("subTrackMomentum_c", "momentum of tracks in the subjet", 50, 0., 15.); 
  book<TH1F>("subTrackMomentum_uds", "momentum of tracks in the subjet", 50, 0., 15.); 
  book<TH1F>("subTrackMomentum_g", "momentum of tracks in the subjet", 50, 0., 15.); 
  book<TH1F>("subTrackMomentum_none", "momentum of tracks in the subjet", 50, 0., 15.); 
  book<TH1F>("subTrackMomentum_data", "momentum of tracks in the subjet", 50, 0., 15.); 

  book<TH1F>("subTrackEta_b", "pseudorapidity of tracks in the subjet", 100, -5., 5.);  
  book<TH1F>("subTrackEta_c", "pseudorapidity of tracks in the subjet", 100, -5., 5.); 
  book<TH1F>("subTrackEta_uds", "pseudorapidity of tracks in the subjet", 100, -5., 5.); 
  book<TH1F>("subTrackEta_g", "pseudorapidity of tracks in the subjet", 100, -5., 5.); 
  book<TH1F>("subTrackEta_none", "pseudorapidity of tracks in the subjet", 100, -5., 5.); 
  book<TH1F>("subTrackEta_data", "pseudorapidity of tracks in the subjet", 100, -5., 5.); 

  book<TH1F>("subTrackEtaRel_b", "track pseudorapidity, relative to the jet axis", 100, 0., 5.);  
  book<TH1F>("subTrackEtaRel_c", "track pseudorapidity, relative to the jet axis", 100, 0., 5.); 
  book<TH1F>("subTrackEtaRel_uds", "track pseudorapidity, relative to the jet axis", 100, 0., 5.); 
  book<TH1F>("subTrackEtaRel_g", "track pseudorapidity, relative to the jet axis", 100, 0., 5.); 
  book<TH1F>("subTrackEtaRel_none", "track pseudorapidity, relative to the jet axis", 100, 0., 5.); 
  book<TH1F>("subTrackEtaRel_data", "track pseudorapidity, relative to the jet axis", 100, 0., 5.);

  book<TH1F>("subTrackDeltaR_b", "track pseudoangular distance from the jet axis", 50, 0., 0.5);  
  book<TH1F>("subTrackDeltaR_c", "track pseudoangular distance from the jet axis", 50, 0., 0.5); 
  book<TH1F>("subTrackDeltaR_uds", "track pseudoangular distance from the jet axis", 50, 0., 0.5); 
  book<TH1F>("subTrackDeltaR_g", "track pseudoangular distance from the jet axis", 50, 0., 0.5); 
  book<TH1F>("subTrackDeltaR_none", "track pseudoangular distance from the jet axis", 50, 0., 0.5); 
  book<TH1F>("subTrackDeltaR_data", "track pseudoangular distance from the jet axis", 50, 0., 0.5); 

  book<TH1F>("subTrackSip3dVal_b", "track 3D signed impact parameter", 100, -0.05, 0.1);  
  book<TH1F>("subTrackSip3dVal_c", "track 3D signed impact parameter", 100, -0.05, 0.1); 
  book<TH1F>("subTrackSip3dVal_uds", "track 3D signed impact parameter", 100, -0.05, 0.1); 
  book<TH1F>("subTrackSip3dVal_g", "track 3D signed impact parameter", 100, -0.05, 0.1); 
  book<TH1F>("subTrackSip3dVal_none", "track 3D signed impact parameter", 100, -0.05, 0.1); 
  book<TH1F>("subTrackSip3dVal_data", "track 3D signed impact parameter", 100, -0.05, 0.1); 

  book<TH1F>("subTrackSip3dSig_b", "track 3D signed impact parameter significance", 100, -35., 35.);  
  book<TH1F>("subTrackSip3dSig_c", "track 3D signed impact parameter significance", 100, -35., 35.); 
  book<TH1F>("subTrackSip3dSig_uds", "track 3D signed impact parameter significance", 100, -35., 35.); 
  book<TH1F>("subTrackSip3dSig_g", "track 3D signed impact parameter significance", 100, -35., 35.); 
  book<TH1F>("subTrackSip3dSig_none", "track 3D signed impact parameter significance", 100, -35., 35.); 
  book<TH1F>("subTrackSip3dSig_data", "track 3D signed impact parameter significance", 100, -35., 35.); 

  book<TH1F>("subTrackSip2dVal_b", "track 2D signed impact parameter", 50, -0.2, 0.2);  
  book<TH1F>("subTrackSip2dVal_c", "track 2D signed impact parameter", 50, -0.2, 0.2); 
  book<TH1F>("subTrackSip2dVal_uds", "track 2D signed impact parameter", 50, -0.2, 0.2); 
  book<TH1F>("subTrackSip2dVal_g", "track 2D signed impact parameter", 50, -0.2, 0.2); 
  book<TH1F>("subTrackSip2dVal_none", "track 2D signed impact parameter", 50, -0.2, 0.2); 
  book<TH1F>("subTrackSip2dVal_data", "track 2D signed impact parameter", 50, -0.2, 0.2); 

  book<TH1F>("subTrackSip2dSig_b", "track 2D signed impact parameter significance", 100, -10., 10.);  
  book<TH1F>("subTrackSip2dSig_c", "track 2D signed impact parameter significance", 100, -10., 10.); 
  book<TH1F>("subTrackSip2dSig_uds", "track 2D signed impact parameter significance", 100, -10., 10.); 
  book<TH1F>("subTrackSip2dSig_g", "track 2D signed impact parameter significance", 100, -10., 10.); 
  book<TH1F>("subTrackSip2dSig_none", "track 2D signed impact parameter significance", 100, -10., 10.); 
  book<TH1F>("subTrackSip2dSig_data", "track 2D signed impact parameter significance", 100, -10., 10.); 

  book<TH1F>("subTrackDecayLenVal_b", "track decay length", 100, 0., 25.);  
  book<TH1F>("subTrackDecayLenVal_c", "track decay length", 100, 0., 25.); 
  book<TH1F>("subTrackDecayLenVal_uds", "track decay length", 100, 0., 25.); 
  book<TH1F>("subTrackDecayLenVal_g", "track decay length", 100, 0., 25.); 
  book<TH1F>("subTrackDecayLenVal_none", "track decay length", 100, 0., 25.); 
  book<TH1F>("subTrackDecayLenVal_data", "track decay length", 100, 0., 25.); 

  book<TH1F>("subTrackChi2_b", "track fit chi2", 50, 0., 5.);  
  book<TH1F>("subTrackChi2_c", "track fit chi2", 50, 0., 5.); 
  book<TH1F>("subTrackChi2_uds", "track fit chi2", 50, 0., 5.); 
  book<TH1F>("subTrackChi2_g", "track fit chi2", 50, 0., 5.); 
  book<TH1F>("subTrackChi2_none", "track fit chi2", 50, 0., 5.); 
  book<TH1F>("subTrackChi2_data", "track fit chi2", 50, 0., 5.); 

  book<TH1F>("subTrackNTotalHits_b", "number of valid total hits", 20, 6., 26.);  
  book<TH1F>("subTrackNTotalHits_c", "number of valid total hits", 20, 6., 26.); 
  book<TH1F>("subTrackNTotalHits_uds", "number of valid total hits", 20, 6., 26.); 
  book<TH1F>("subTrackNTotalHits_g", "number of valid total hits", 20, 6., 26.); 
  book<TH1F>("subTrackNTotalHits_none", "number of valid total hits", 20, 6., 26.); 
  book<TH1F>("subTrackNTotalHits_data", "number of valid total hits", 20, 6., 26.); 

  book<TH1F>("subTrackNPixelHits_b", "number of valid pixel hits", 9, 0., 9.);  
  book<TH1F>("subTrackNPixelHits_c", "number of valid pixel hits", 9, 0., 9.); 
  book<TH1F>("subTrackNPixelHits_uds", "number of valid pixel hits", 9, 0., 9.); 
  book<TH1F>("subTrackNPixelHits_g", "number of valid pixel hits", 9, 0., 9.); 
  book<TH1F>("subTrackNPixelHits_none", "number of valid pixel hits", 9, 0., 9.); 
  book<TH1F>("subTrackNPixelHits_data", "number of valid pixel hits", 9, 0., 9.); 

  book<TH1F>("subTrackPtRel_b", "track transverse momentum, relative to the jet axis", 50, 0., 6.);  
  book<TH1F>("subTrackPtRel_c", "track transverse momentum, relative to the jet axis", 50, 0., 6.); 
  book<TH1F>("subTrackPtRel_uds", "track transverse momentum, relative to the jet axis", 50, 0., 6.); 
  book<TH1F>("subTrackPtRel_g", "track transverse momentum, relative to the jet axis", 50, 0., 6.); 
  book<TH1F>("subTrackPtRel_none", "track transverse momentum, relative to the jet axis", 50, 0., 6.); 
  book<TH1F>("subTrackPtRel_data", "track transverse momentum, relative to the jet axis", 50, 0., 6.); 

  book<TH1F>("subTrackPPar_b", "track parallel momentum, along the jet axis", 100, 0., 50.);  
  book<TH1F>("subTrackPPar_c", "track parallel momentum, along the jet axis", 100, 0., 50.); 
  book<TH1F>("subTrackPPar_uds", "track parallel momentum, along the jet axis", 100, 0., 50.); 
  book<TH1F>("subTrackPPar_g", "track parallel momentum, along the jet axis", 100, 0., 50.); 
  book<TH1F>("subTrackPPar_none", "track parallel momentum, along the jet axis", 100, 0., 50.); 
  book<TH1F>("subTrackPPar_data", "track parallel momentum, along the jet axis", 100, 0., 50.); 

  book<TH1F>("subTrackPtRatio_b", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5);  
  book<TH1F>("subTrackPtRatio_c", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5); 
  book<TH1F>("subTrackPtRatio_uds", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5); 
  book<TH1F>("subTrackPtRatio_g", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5); 
  book<TH1F>("subTrackPtRatio_none", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5); 
  book<TH1F>("subTrackPtRatio_data", "track transverse momentum, relative to the jet axis, normalized to its energy", 50, 0., 0.5); 

  book<TH1F>("subTrackPParRatio_b", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1);  
  book<TH1F>("subTrackPParRatio_c", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1); 
  book<TH1F>("subTrackPParRatio_uds", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1); 
  book<TH1F>("subTrackPParRatio_g", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1); 
  book<TH1F>("subTrackPParRatio_none", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1); 
  book<TH1F>("subTrackPParRatio_data", "track parallel momentum, along the jet axis, normalized to its energy", 100, 0.9, 1.1); 

  book<TH1F>("subTrackJetDistVal_b", "minimum track approach distance to jet axis", 100, -0.04, 0.01);  
  book<TH1F>("subTrackJetDistVal_c", "minimum track approach distance to jet axis", 100, -0.04, 0.01); 
  book<TH1F>("subTrackJetDistVal_uds", "minimum track approach distance to jet axis", 100, -0.04, 0.01); 
  book<TH1F>("subTrackJetDistVal_g", "minimum track approach distance to jet axis", 100, -0.04, 0.01); 
  book<TH1F>("subTrackJetDistVal_none", "minimum track approach distance to jet axis", 100, -0.04, 0.01); 
  book<TH1F>("subTrackJetDistVal_data", "minimum track approach distance to jet axis", 100, -0.04, 0.01); 
 
  book<TH1F>("subTrackJetDistSig_b", "minimum track approach distance to jet axis significance", 50, 0., 0.1);  
  book<TH1F>("subTrackJetDistSig_c", "minimum track approach distance to jet axis significance", 50, 0., 0.1); 
  book<TH1F>("subTrackJetDistSig_uds", "minimum track approach distance to jet axis significance", 50, 0., 0.1); 
  book<TH1F>("subTrackJetDistSig_g", "minimum track approach distance to jet axis significance", 50, 0., 0.1); 
  book<TH1F>("subTrackJetDistSig_none", "minimum track approach distance to jet axis significance", 50, 0., 0.1); 
  book<TH1F>("subTrackJetDistSig_data", "minimum track approach distance to jet axis significance", 50, 0., 0.1); 

  book<TH1F>("subTrackGhostTrackDistVal_b", "minimum approach distance to ghost track", 100, 0., 0.05);  
  book<TH1F>("subTrackGhostTrackDistVal_c", "minimum approach distance to ghost track", 100, 0., 0.05); 
  book<TH1F>("subTrackGhostTrackDistVal_uds", "minimum approach distance to ghost track", 100, 0., 0.05); 
  book<TH1F>("subTrackGhostTrackDistVal_g", "minimum approach distance to ghost track", 100, 0., 0.05); 
  book<TH1F>("subTrackGhostTrackDistVal_none", "minimum approach distance to ghost track", 100, 0., 0.05); 
  book<TH1F>("subTrackGhostTrackDistVal_data", "minimum approach distance to ghost track", 100, 0., 0.05); 

  book<TH1F>("subTrackGhostTrackDistSig_b", "minimum approach distance to ghost track significance", 50, 0., 5.);  
  book<TH1F>("subTrackGhostTrackDistSig_c", "minimum approach distance to ghost track significance", 50, 0., 5.); 
  book<TH1F>("subTrackGhostTrackDistSig_uds", "minimum approach distance to ghost track significance", 50, 0., 5.); 
  book<TH1F>("subTrackGhostTrackDistSig_g", "minimum approach distance to ghost track significance", 50, 0., 5.); 
  book<TH1F>("subTrackGhostTrackDistSig_none", "minimum approach distance to ghost track significance", 50, 0., 5.); 
  book<TH1F>("subTrackGhostTrackDistSig_data", "minimum approach distance to ghost track significance", 50, 0., 5.); 

  book<TH1F>("subTrackGhostTrackWeight_b", "weight of track participation in ghost track fit", 100, -0.5, 1.5);  
  book<TH1F>("subTrackGhostTrackWeight_c", "weight of track participation in ghost track fit", 100, -0.5, 1.5); 
  book<TH1F>("subTrackGhostTrackWeight_uds", "weight of track participation in ghost track fit", 100, -0.5, 1.5); 
  book<TH1F>("subTrackGhostTrackWeight_g", "weight of track participation in ghost track fit", 100, -0.5, 1.5); 
  book<TH1F>("subTrackGhostTrackWeight_none", "weight of track participation in ghost track fit", 100, -0.5, 1.5); 
  book<TH1F>("subTrackGhostTrackWeight_data", "weight of track participation in ghost track fit", 100, -0.5, 1.5);

  //secondary vertex tag info

  book<TH1F>("subFlightDistance2dVal_b", "transverse distance between primary and secondary vertex", 50, 0., 3.);  
  book<TH1F>("subFlightDistance2dVal_c", "transverse distance between primary and secondary vertex", 50, 0., 3.); 
  book<TH1F>("subFlightDistance2dVal_uds", "transverse distance between primary and secondary vertex", 50, 0., 3.); 
  book<TH1F>("subFlightDistance2dVal_g", "transverse distance between primary and secondary vertex", 50, 0., 3.); 
  book<TH1F>("subFlightDistance2dVal_none", "transverse distance between primary and secondary vertex", 50, 0., 3.); 
  book<TH1F>("subFlightDistance2dVal_data", "transverse distance between primary and secondary vertex", 50, 0., 3.); 

  book<TH1F>("subFlightDistance2dSig_b", "transverse distance significance between primary and secondary vertex", 50, 0., 50.);  
  book<TH1F>("subFlightDistance2dSig_c", "transverse distance significance between primary and secondary vertex", 50, 0., 50.); 
  book<TH1F>("subFlightDistance2dSig_uds", "transverse distance significance between primary and secondary vertex", 50, 0., 50.); 
  book<TH1F>("subFlightDistance2dSig_g", "transverse distance significance between primary and secondary vertex", 50, 0., 50.); 
  book<TH1F>("subFlightDistance2dSig_none", "transverse distance significance between primary and secondary vertex", 50, 0., 50.); 
  book<TH1F>("subFlightDistance2dSig_data", "transverse distance significance between primary and secondary vertex", 50, 0., 50.);

  book<TH1F>("subFlightDistance3dVal_b", "distance between primary and secondary vertex", 50, 0., 10.);  
  book<TH1F>("subFlightDistance3dVal_c", "distance between primary and secondary vertex", 50, 0., 10.); 
  book<TH1F>("subFlightDistance3dVal_uds", "distance between primary and secondary vertex", 50, 0., 10.); 
  book<TH1F>("subFlightDistance3dVal_g", "distance between primary and secondary vertex", 50, 0., 10.); 
  book<TH1F>("subFlightDistance3dVal_none", "distance between primary and secondary vertex", 50, 0., 10.); 
  book<TH1F>("subFlightDistance3dVal_data", "distance between primary and secondary vertex", 50, 0., 10.); 

  book<TH1F>("subFlightDistance3dSig_b", "distance significance between primary and secondary vertex", 100, 0., 80.);  
  book<TH1F>("subFlightDistance3dSig_c", "distance significance between primary and secondary vertex", 100, 0., 80.); 
  book<TH1F>("subFlightDistance3dSig_uds", "distance significance between primary and secondary vertex", 100, 0., 80.); 
  book<TH1F>("subFlightDistance3dSig_g", "distance significance between primary and secondary vertex", 100, 0., 80.); 
  book<TH1F>("subFlightDistance3dSig_none", "distance significance between primary and secondary vertex", 100, 0., 80.); 
  book<TH1F>("subFlightDistance3dSig_data", "distance significance between primary and secondary vertex", 100, 0., 80.); 

  book<TH1F>("subVertexJetDeltaR_b", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.5);  
  book<TH1F>("subVertexJetDeltaR_c", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.5); 
  book<TH1F>("subVertexJetDeltaR_uds", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.); 
  book<TH1F>("subVertexJetDeltaR_g", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.5); 
  book<TH1F>("subVertexJetDeltaR_none", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.5); 
  book<TH1F>("subVertexJetDeltaR_data", "pseudoangular distance between jet axis and secondary vertex direction", 50, 0., 0.5); 

  book<TH1F>("subJetNSecondaryVertices_b", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.);  
  book<TH1F>("subJetNSecondaryVertices_c", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.); 
  book<TH1F>("subJetNSecondaryVertices_uds", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.); 
  book<TH1F>("subJetNSecondaryVertices_g", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.); 
  book<TH1F>("subJetNSecondaryVertices_none", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.); 
  book<TH1F>("subJetNSecondaryVertices_data", "number of reconstructed possible secondary vertices in jet", 8, 0., 8.); 

  book<TH1F>("subVertexNTracks_b", "number of tracks at secondary vertex", 20, 0., 20.);  
  book<TH1F>("subVertexNTracks_c", "number of tracks at secondary vertex", 20, 0., 20.); 
  book<TH1F>("subVertexNTracks_uds", "number of tracks at secondary vertex", 20, 0., 20.); 
  book<TH1F>("subVertexNTracks_g", "number of tracks at secondary vertex", 20, 0., 20.); 
  book<TH1F>("subVertexNTracks_none", "number of tracks at secondary vertex", 20, 0., 20.); 
  book<TH1F>("subVertexNTracks_data", "number of tracks at secondary vertex", 20, 0., 20.); 

  book<TH1F>("subSecondaryVertex_b", "secondary vertex uncorrected mass", 50, 0., 10.);  
  book<TH1F>("subSecondaryVertex_c", "secondary vertex uncorrected mass", 50, 0., 10.); 
  book<TH1F>("subSecondaryVertex_uds", "secondary vertex uncorrected mass", 50, 0., 10.); 
  book<TH1F>("subSecondaryVertex_g", "secondary vertex uncorrected mass", 50, 0., 10.); 
  book<TH1F>("subSecondaryVertex_none", "secondary vertex uncorrected mass", 50, 0., 10.); 
  book<TH1F>("subSecondaryVertex_data", "secondary vertex uncorrected mass", 50, 0., 10.); 

  book<TH1F>("subVertexChi2_b", "secondary vertex chi2", 50, 0., 10.);  
  book<TH1F>("subVertexChi2_c", "secondary vertex chi2", 50, 0., 10.); 
  book<TH1F>("subVertexChi2_uds", "secondary vertex chi2", 50, 0., 10.); 
  book<TH1F>("subVertexChi2_g", "secondary vertex chi2", 50, 0., 10.); 
  book<TH1F>("subVertexChi2_none", "secondary vertex chi2", 50, 0., 10.); 
  book<TH1F>("subVertexChi2_data", "secondary vertex chi2", 50, 0., 10.); 

  book<TH1F>("subVertexNdof_b", "secondary vertex fit dergrees of frendom", 30, 0., 30.);  
  book<TH1F>("subVertexNdof_c", "secondary vertex fit dergrees of frendom", 30, 0., 30.); 
  book<TH1F>("subVertexNdof_uds", "secondary vertex fit dergrees of frendom", 30, 0., 30.); 
  book<TH1F>("subVertexNdof_g", "secondary vertex fit dergrees of frendom", 30, 0., 30.); 
  book<TH1F>("subVertexNdof_none", "secondary vertex fit dergrees of frendom", 300, 0., 30.); 
  book<TH1F>("subVertexNdof_data", "secondary vertex fit dergrees of frendom", 300, 0., 30.); 

  book<TH1F>("subVertexNormalizedChi2_b", "secondary vertex fit normalized chi2", 100, 0., 10.);  
  book<TH1F>("subVertexNormalizedChi2_c", "secondary vertex fit normalized chi2", 100, 0., 10.); 
  book<TH1F>("subVertexNormalizedChi2_uds", "secondary vertex fit normalized chi2", 100, 0., 10.); 
  book<TH1F>("subVertexNormalizedChi2_g", "secondary vertex fit normalized chi2", 100, 0., 10.); 
  book<TH1F>("subVertexNormalizedChi2_none", "secondary vertex fit normalized chi2", 100, 0., 10.); 
  book<TH1F>("subVertexNormalizedChi2_data", "secondary vertex fit normalized chi2", 100, 0., 10.); 



  //JTC SV variables
  book<TH1F>("subVertexCategoryJTC_b", "secondary vertex category from jet tag computer", 5, 0., 5.);  
  book<TH1F>("subVertexCategoryJTC_c", "secondary vertex category from jet tag computer", 5, 0., 5.); 
  book<TH1F>("subVertexCategoryJTC_uds", "secondary vertex category from jet tag computer", 5, 0., 5.); 
  book<TH1F>("subVertexCategoryJTC_g", "secondary vertex category from jet tag computer", 5, 0., 5.); 
  book<TH1F>("subVertexCategoryJTC_none", "secondary vertex category from jet tag computer", 5, 0., 5.); 
  book<TH1F>("subVertexCategoryJTC_data", "secondary vertex category from jet tag computer", 5, 0., 5.); 

  book<TH1F>("subVertexMassJTC_b", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02);  
  book<TH1F>("subVertexMassJTC_c", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02); 
  book<TH1F>("subVertexMassJTC_uds", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02); 
  book<TH1F>("subVertexMassJTC_g", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02); 
  book<TH1F>("subVertexMassJTC_none", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02); 
  book<TH1F>("subVertexMassJTC_data", "secondary vertex corrected mass from jet tag computer", 100, 0., 0.02); 

  book<TH1F>("subVertexEnergyRatioJTC_b", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.);  
  book<TH1F>("subVertexEnergyRatioJTC_c", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.); 
  book<TH1F>("subVertexEnergyRatioJTC_uds", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.); 
  book<TH1F>("subVertexEnergyRatioJTC_g", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.); 
  book<TH1F>("subVertexEnergyRatioJTC_none", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.); 
  book<TH1F>("subVertexEnergyRatioJTC_data", "ratio of energy at secondary vertex over total energy from JTC", 100, 0., 2.); 

  book<TH1F>("subTrackSip3dSigAboveCharmJTC_b", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02);  
  book<TH1F>("subTrackSip3dSigAboveCharmJTC_c", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02); 
  book<TH1F>("subTrackSip3dSigAboveCharmJTC_uds", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02); 
  book<TH1F>("subTrackSip3dSigAboveCharmJTC_g", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02); 
  book<TH1F>("subTrackSip3dSigAboveCharmJTC_none", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02); 
  book<TH1F>("subTrackSip3dSigAboveCharmJTC_data", "track 3D signed impact parameter significance of first track lifting mass above charm from JTC", 100, 0., 0.02); 

  book<TH1F>("subTrackMultiplicity_b", "track multiplicity of the subjet", 50, 0., 50.);  
  book<TH1F>("subTrackMultiplicity_c", "track multiplicity of the subjet", 50, 0., 50.); 
  book<TH1F>("subTrackMultiplicity_uds", "track multiplicity of the subjet", 50, 0., 50.); 
  book<TH1F>("subTrackMultiplicity_g", "track multiplicity of the subjet", 50, 0., 50.); 
  book<TH1F>("subTrackMultiplicity_none", "track multiplicity of the subjet", 50, 0., 50.); 
  book<TH1F>("subTrackMultiplicity_data", "track multiplicity of the subjet", 50, 0., 50.); 

  book<TH1F>("subTrackPt_b", "track transverse momentum", 100, 0., 50.);  
  book<TH1F>("subTrackPt_c", "track transverse momentum", 100, 0., 50.); 
  book<TH1F>("subTrackPt_uds", "track transverse momentum", 100, 0., 50.); 
  book<TH1F>("subTrackPt_g", "track transverse momentum", 100, 0., 50.); 
  book<TH1F>("subTrackPt_none", "track transverse momentum", 100, 0., 50.); 
  book<TH1F>("subTrackPt_data", "track transverse momentum", 100, 0., 50.); 

  book<TH1F>("weight_b", "weight", 100, 0., 0.1);  
  book<TH1F>("weight_c", "weight", 100, 0., 0.1); 
  book<TH1F>("weight_uds", "weight", 100, 0., 0.1); 
  book<TH1F>("weight_g", "weight", 100, 0., 0.1); 
  book<TH1F>("weight_none", "weight", 100, 0., 0.1); 
  book<TH1F>("weight_data", "weight", 100, 0., 0.1); 

  book<TH1F>("MassTop_corr", "Top Mass corr", 50, 0., 500.); 
  book<TH1F>("MassTop_sub", "Top Mass calculated from subjets", 50, 0., 500.);
  book<TH1F>("MassTop_SD", "Top Mass SoftDrop", 50, 0., 500.); 
  book<TH1F>("MassTop_SD_corr", "Top Mass SoftDrop corrected", 50, 0., 500.);
 book<TH1F>("prunedmass", "pruned mass", 50, 0., 500.);
 
  book<TH1F>("PTTop", "Top PT", 100, 0., 2000.);  

  book<TH1F>("subVertexNvtx_b", "N of secondary vertex", 6, 0., 6.);  
  book<TH1F>("subVertexNvtx_c", "N of secondary vertex", 6, 0., 6.); 
  book<TH1F>("subVertexNvtx_uds", "N of secondary vertex", 6, 0., 6.); 
  book<TH1F>("subVertexNvtx_g", "N of secondary vertex", 6, 0., 6.); 
  book<TH1F>("subVertexNvtx_none", "N of secondary vertex", 6, 0., 6.); 
  book<TH1F>("subVertexNvtx_data", "N of secondary vertex", 6, 0., 6.); 

  book<TH1F>("PrimaryVertex", "Primary Vertex", 50, 0., 50.);  

  book<TH1F>("Weight", "Weight", 100, -0.3, 0.3);
  book<TH1F>("NumberofEvents", "Number of Events", 6, 0., 6.);

  book<TH1F>("m12", "m12", 20, 0., 100.);
  book<TH1F>("m13", "m13", 20, 0., 100.);
  book<TH1F>("m23", "m23", 20, 0., 100.);
 
  book<TH1F>("fRec", "fRec", 50, 0., 1.);

  book<TH1F>("HTTmass", "HTTmass", 50, 0., 300.);
  book<TH1F>("tau32", "tau32", 50, 0., 1.);
  book<TH1F>("tau21", "tau21", 50, 0., 1.);

  book<TH1F>("wmass", "wmass", 50, 0., 150.);
  book<TH1F>("neutralEmEnergyFraction", "neutralEmEnergyFraction", 50, 0., 1.);
  book<TH1F>("neutralHadronEnergyFraction", "neutralHadronEnergyFraction", 50, 0., 1.);
  book<TH1F>("neutralMultiplicity", "neutralMultiplicity", 20, 0., 20.);

  book<TH1F>("tau3", "tau3", 50, 0., 1.);
  book<TH1F>("tau2", "tau2", 50, 0., 1.);

  book<TH1F>("subCSV", "combined secondary vertex discriminator of the subjet", 100, 0., 1.);  


  book<TH1F>("subjetPT_b", "PT of subjet with highest CSV", 100, 0., 1500.);
  book<TH1F>("subjetPT_c", "PT of subjet with highest CSV", 100, 0., 1500.);
  book<TH1F>("subjetPT_udsg", "PT of subjet with highest CSV", 100, 0., 1500.);

  book<TH1F>("subjetPT", "PT of subjet with highest CSV", 100, 0., 1500.);
  book<TH1F>("subjethadronFlavor", "hadronFlavour of subjet with highest CSV", 100, 0., 1.);

  book<TH1F>("eta", "eta", 100, -3., 3.);
  book<TH1F>("rapidity", "rapidity", 100, -10., 10.);
  book<TH1F>("BoostedDoubleSecondaryVertexAK8", "BoostedDoubleSecondaryVertexAK8", 20, -1., 1.);
  book<TH1F>("BoostedDoubleSecondaryVertexAK8_neg", "BoostedDoubleSecondaryVertexAK8_neg", 100, -15., 15.);

  book<TH1F>("subFlavour_top_A", "flavour of the top subjet", 6, 0., 6.); 
  book<TH1F>("subFlavour_top_B", "flavour of the top subjet", 6, 0., 6.);

  book<TH1F>("z_ratio", "z_ratio" , 20, 0., 60.);
  book<TH1F>("trackSipdSig_3", "trackSipdSig_3" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_2", "trackSipdSig_2" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_1", "trackSipdSig_1" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_0",  "trackSipdSig_0", 20, -20., 20.);
  book<TH1F>("trackSipdSig_1_0", "trackSipdSig_1_0" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_0_0", "trackSipdSig_0_0" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_1_1", "trackSipdSig_1_1" , 20, -20., 20.);
  book<TH1F>("trackSipdSig_0_1", "trackSipdSig_0_1" , 20, -20., 20.);
  book<TH1F>("trackSip2dSigAboveCharm_0", "trackSip2dSigAboveCharm_0" , 20, -20., 20.);
  book<TH1F>("trackSip2dSigAboveBottom_0","trackSip2dSigAboveBottom_0"  , 20, -20., 20.);
  book<TH1F>("trackSip2dSigAboveBottom_1", "trackSip2dSigAboveBottom_1" , 20, -20., 20.);
  book<TH1F>("tau1_trackEtaRel_0",  "tau1_trackEtaRel_0", 20, 0., 10.);
  book<TH1F>("tau1_trackEtaRel_1", "tau1_trackEtaRel_1" , 20, 0., 10.);
  book<TH1F>("tau1_trackEtaRel_2", "tau1_trackEtaRel_2" , 20, 0., 10.);
  book<TH1F>("tau0_trackEtaRel_0","tau0_trackEtaRel_0"  , 20, 0., 10.);
  book<TH1F>("tau0_trackEtaRel_1","tau0_trackEtaRel_1"  , 20, 0., 10.);
  book<TH1F>("tau0_trackEtaRel_2", "tau0_trackEtaRel_2" , 20, 0., 10.);
  book<TH1F>("tau_vertexMass_0", "tau_vertexMass_0" , 9, 0., 27.);
  book<TH1F>("tau_vertexEnergyRatio_0", "tau_vertexEnergyRatio_0" , 20, 0., 4.);
  book<TH1F>("tau_vertexDeltaR_0", "tau_vertexDeltaR_0" , 20, -0.05, 1.05);
  book<TH1F>("tau_flightDistance2dSig_0", "tau_flightDistance2dSig_0" , 20, -1., 21.);
  book<TH1F>("tau_vertexMass_1", "tau_vertexMass_1" , 9, 0., 27.);
  book<TH1F>("tau_vertexEnergyRatio_1", "tau_vertexEnergyRatio_1" , 20, 0., 4.);
  book<TH1F>("tau_flightDistance2dSig_1", "tau_flightDistance2dSig_1" , 20, -1., 21.);
  book<TH1F>("jetNTracks", "jetNTracks" , 20, 0., 40.);
  book<TH1F>("nSV", "nSV" , 8, 0., 8.);


}

template<typename T>
double m_groomedT(const T & topjet){
  auto subjets = topjet.subjets();
  LorentzVector sum(0,0,0,0);
  for(auto subjet : subjets) sum += subjet.v4();
  if(!sum.isTimelike()) return -1.0;
  else return sum.M();
}
double M_groomed(const TopJet & topjet){
  return m_groomedT<TopJet>(topjet);
}

void Hists_sub::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  float weight = event.weight;
  
  //get extra jet collections


  
  std::vector<TopJet>* topjets = event.topjets;
  std::vector<Muon>* muons = event.muons;
 
  int check_one_event = 0;
  unsigned int takehighestpt = 0;
  if(topjets->size()>1)
    {
      double ptTopJet[topjets->size()];

      for(unsigned int j=0;j<topjets->size();j++){
	ptTopJet[j] = topjets->at(j).pt();
      }

      int tempPT = 0;
	  
      for(unsigned int k=0;k<topjets->size();k++)
	{
	  if(ptTopJet[k]>tempPT){tempPT=ptTopJet[k]; takehighestpt = k;}	    
	}
    }

  for(unsigned int n=0;n<topjets->size();n++){
    if (muons->size() == 0) continue; 

    if(topjets->size()>1)
      {
	if (takehighestpt!=n) continue;
      }
    TopJet topjet=topjets->at(n);
    double deltaphi=deltaPhi(topjet,muons->at(0));
    double pi = 3.14159265359;
    if(!((deltaphi>(2*pi/3))&&(topjet.pt()>300.)&&(fabs(topjet.eta())<2.4))) continue;


    auto subjets=topjet.subjets();

    sort_by_pt(subjets); 

  
    double m12 = 0;
    double m13 = 0;
    double m23 = 0;



    if(subjets.size()==3) {    
      
      if( (subjets[0].v4()+subjets[1].v4()).isTimelike())
	m12=(subjets[0].v4()+subjets[1].v4()).M();
      
      if( (subjets[0].v4()+subjets[2].v4()).isTimelike() )
	m13=(subjets[0].v4()+subjets[2].v4()).M();
      
      if( (subjets[1].v4()+subjets[2].v4()).isTimelike()  )
	m23 = (subjets[1].v4()+subjets[2].v4()).M();

      hist("m12")->Fill(m12, weight);
      hist("m13")->Fill(m13, weight);
      hist("m23")->Fill(m23, weight);


      }
  

    check_one_event++;
    if(check_one_event == 1) hist("NumberofEvents")->Fill(1,weight);
       
    
 
    hist("PTTop")->Fill(topjet.v4().pt(), weight);
    hist("PrimaryVertex")->Fill(event.pvs->size(), weight);
    hist("Weight")->Fill(weight);
    hist("MassTop_sub")->Fill(M_groomed(topjet),weight);
    hist("MassTop_SD")->Fill(topjet.softdropmass(),weight);
    hist("prunedmass")->Fill(topjet.prunedmass(),weight);
    hist("MassTop_SD_corr")->Fill(topjet.softdropmass()*1/topjet.JEC_factor_raw(),weight);

    hist("neutralEmEnergyFraction")->Fill(topjet.neutralEmEnergyFraction(),weight);
    hist("neutralHadronEnergyFraction")->Fill(topjet.neutralHadronEnergyFraction(),weight);
    hist("neutralMultiplicity")->Fill(topjet.neutralMultiplicity(),weight);

    if (topjet.has_tag(topjet.tagname2tag("fRec"))) hist("fRec")->Fill(topjet.get_tag(topjet.tagname2tag("fRec")),weight);
    if (topjet.has_tag(topjet.tagname2tag("mass"))) hist("HTTmass")->Fill(topjet.get_tag(topjet.tagname2tag("mass")),weight);

    hist("tau32")->Fill(topjet.tau3()/topjet.tau2(), weight);
    hist("tau21")->Fill(topjet.tau2()/topjet.tau1(), weight);
    hist("tau3")->Fill(topjet.tau3(), weight);
    hist("tau2")->Fill(topjet.tau2(), weight);

    hist("MassTop_corr")->Fill(topjet.v4().M(), weight);
    hist("eta")->Fill(topjet.eta(), weight);
    hist("rapidity")->Fill(topjet.v4().Rapidity(), weight);
   
    hist("subCSV")->Fill(topjet.btag_combinedSecondaryVertex(),weight);
    hist("BoostedDoubleSecondaryVertexAK8")->Fill(topjet.btag_BoostedDoubleSecondaryVertexAK8(),weight);
    hist("BoostedDoubleSecondaryVertexAK8_neg")->Fill(topjet.btag_BoostedDoubleSecondaryVertexAK8(),weight);

    hist("z_ratio")->Fill(topjet.get_tag(topjet.tagname2tag("z_ratio")), weight);
    hist("trackSipdSig_3")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_3")), weight);
    hist("trackSipdSig_2")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_2")), weight);
    hist("trackSipdSig_1")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_1")), weight);
    hist("trackSipdSig_0")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_0")), weight);
    hist("trackSipdSig_1_0")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_1_0")), weight);
    hist("trackSipdSig_0_0")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_0_0")), weight);
    hist("trackSipdSig_1_1")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_1_1")), weight);
    hist("trackSipdSig_0_1")->Fill(topjet.get_tag(topjet.tagname2tag("trackSipdSig_0_1")), weight);
    hist("trackSip2dSigAboveCharm_0")->Fill(topjet.get_tag(topjet.tagname2tag("trackSip2dSigAboveCharm_0")), weight);
    hist("trackSip2dSigAboveBottom_0")->Fill(topjet.get_tag(topjet.tagname2tag("trackSip2dSigAboveBottom_0")), weight);
    hist("trackSip2dSigAboveBottom_1")->Fill(topjet.get_tag(topjet.tagname2tag("trackSip2dSigAboveBottom_1")), weight);
    hist("tau1_trackEtaRel_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau1_trackEtaRel_0")), weight);
    hist("tau1_trackEtaRel_1")->Fill(topjet.get_tag(topjet.tagname2tag("tau1_trackEtaRel_1")), weight);
    hist("tau1_trackEtaRel_2")->Fill(topjet.get_tag(topjet.tagname2tag("tau1_trackEtaRel_2")), weight);
    hist("tau0_trackEtaRel_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau0_trackEtaRel_0")), weight);
    hist("tau0_trackEtaRel_1")->Fill(topjet.get_tag(topjet.tagname2tag("tau0_trackEtaRel_1")), weight);
    hist("tau0_trackEtaRel_2")->Fill(topjet.get_tag(topjet.tagname2tag("tau0_trackEtaRel_2")), weight);
    hist("tau_vertexMass_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau_vertexMass_0")), weight);
    hist("tau_vertexEnergyRatio_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau_vertexEnergyRatio_0")), weight);
    hist("tau_vertexDeltaR_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau_vertexDeltaR_0")), weight);
    hist("tau_flightDistance2dSig_0")->Fill(topjet.get_tag(topjet.tagname2tag("tau_flightDistance2dSig_0")), weight);
    hist("tau_vertexMass_1")->Fill(topjet.get_tag(topjet.tagname2tag("tau_vertexMass_1")), weight);
    hist("tau_vertexEnergyRatio_1")->Fill(topjet.get_tag(topjet.tagname2tag("tau_vertexEnergyRatio_1")), weight);
    hist("tau_flightDistance2dSig_1")->Fill(topjet.get_tag(topjet.tagname2tag("tau_flightDistance2dSig_1")), weight);
    hist("jetNTracks")->Fill(topjet.get_tag(topjet.tagname2tag("jetNTracks")), weight);
    hist("nSV")->Fill(topjet.get_tag(topjet.tagname2tag("nSV")), weight);

  





    JetId checkbtag=CSVBTag(CSVBTag::WP_LOOSE);
    
    if(subjets.size() == 3)
      {
	if (checkbtag(subjets[0], event)+checkbtag(subjets[1], event)+checkbtag(subjets[2], event) >= 1){
	  double_t wmass = 0.;
	  
	  if(checkbtag(subjets[0], event) && subjets[1].btag_combinedSecondaryVertex() < subjets[0].btag_combinedSecondaryVertex() && subjets[2].btag_combinedSecondaryVertex() < subjets[0].btag_combinedSecondaryVertex()) {wmass = (subjets[1].v4()+subjets[2].v4()).M(); hist("wmass")->Fill(wmass,weight);}
	  if(checkbtag(subjets[1], event) && subjets[0].btag_combinedSecondaryVertex() < subjets[1].btag_combinedSecondaryVertex() && subjets[2].btag_combinedSecondaryVertex() < subjets[1].btag_combinedSecondaryVertex()) {wmass = (subjets[0].v4()+subjets[2].v4()).M(); hist("wmass")->Fill(wmass,weight);}
	  if(checkbtag(subjets[2], event) && subjets[0].btag_combinedSecondaryVertex() < subjets[2].btag_combinedSecondaryVertex() && subjets[1].btag_combinedSecondaryVertex() < subjets[2].btag_combinedSecondaryVertex()) {wmass = (subjets[0].v4()+subjets[1].v4()).M(); hist("wmass")->Fill(wmass,weight);}
	}
      }

    double_t highestCSV = 0;
    double_t PT = 0;
    int flavor = 0;


    for(unsigned int ii=0;ii<subjets.size();ii++){
      Jet subjet=subjets[ii];

      JetBTagInfo btaginfo=subjet.btaginfo();

      if(topjet.btag_BoostedDoubleSecondaryVertexAK8()<-0.7) hist("subFlavour_top_A")->Fill(fabs(subjet.hadronFlavor()),weight);
      else hist("subFlavour_top_B")->Fill(fabs(subjet.hadronFlavor()),weight);


      if (ii == 0) {highestCSV=subjet.btag_combinedSecondaryVertex();
	PT = subjet.v4().pt();
	flavor = subjet.hadronFlavor();}
      if (subjet.btag_combinedSecondaryVertex()>highestCSV) {highestCSV=subjet.btag_combinedSecondaryVertex();
	PT = subjet.v4().pt();
        flavor = subjet.hadronFlavor();}
      
      hist("subCSV")->Fill(subjet.btag_combinedSecondaryVertex(),weight);

      //Flavours
      //b 
      if (subjet.flavor() == 5 || subjet.flavor()==-5)
	{
	  //btag variables
	  hist("subCSV_b")->Fill(subjet.btag_combinedSecondaryVertex(),weight);
	  hist("subFlavour_b")->Fill(weight);

	  //track impact parameter tag info
	  hist("subTrackMultiplicity_b")->Fill(btaginfo.TrackMomentum().size(), weight);
	  if (btaginfo.TrackMomentum().size()>0) {for(unsigned int j=0; j<btaginfo.TrackMomentum().size(); j++) {hist("subTrackMomentum_b")->Fill(btaginfo.TrackMomentum().at(j),weight);}}
	  if (btaginfo.TrackEta().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEta().size(); j++) {hist("subTrackEta_b")->Fill(btaginfo.TrackEta().at(j),weight);}}
	  if (btaginfo.TrackEtaRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEtaRel().size(); j++) {hist("subTrackEtaRel_b")->Fill(btaginfo.TrackEtaRel().at(j),weight);}}
	  if (btaginfo.TrackDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDeltaR().size(); j++) {hist("subTrackDeltaR_b")->Fill(btaginfo.TrackDeltaR().at(j),weight);}}
	  if (btaginfo.TrackSip3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dVal().size(); j++) {hist("subTrackSip3dVal_b")->Fill(btaginfo.TrackSip3dVal().at(j),weight);}}
	  if (btaginfo.TrackSip3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dSig().size(); j++) {hist("subTrackSip3dSig_b")->Fill(btaginfo.TrackSip3dSig().at(j),weight);}}
	  if (btaginfo.TrackSip2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dVal().size(); j++) {hist("subTrackSip2dVal_b")->Fill(btaginfo.TrackSip2dVal().at(j),weight);}}
	  if (btaginfo.TrackSip2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dSig().size(); j++) {hist("subTrackSip2dSig_b")->Fill(btaginfo.TrackSip2dSig().at(j),weight);}}
	  if (btaginfo.TrackDecayLenVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDecayLenVal().size(); j++) {hist("subTrackDecayLenVal_b")->Fill(btaginfo.TrackDecayLenVal().at(j),weight);}}
	  if (btaginfo.TrackChi2().size()>0) {for(unsigned int j=0; j<btaginfo.TrackChi2().size(); j++) {hist("subTrackChi2_b")->Fill(btaginfo.TrackChi2().at(j),weight);}}
	  if (btaginfo.TrackNTotalHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNTotalHits().size(); j++) {hist("subTrackNTotalHits_b")->Fill(btaginfo.TrackNTotalHits().at(j),weight);}}
	  if (btaginfo.TrackNPixelHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNPixelHits().size(); j++) {hist("subTrackNPixelHits_b")->Fill(btaginfo.TrackNPixelHits().at(j),weight);}}
	  if (btaginfo.TrackPtRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRel().size(); j++) {hist("subTrackPtRel_b")->Fill(btaginfo.TrackPtRel().at(j),weight);}}
	  if (btaginfo.TrackPPar().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPPar().size(); j++) {hist("subTrackPPar_b")->Fill(btaginfo.TrackPPar().at(j),weight);}}
	  if (btaginfo.TrackPtRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRatio().size(); j++) {hist("subTrackPtRatio_b")->Fill(btaginfo.TrackPtRatio().at(j),weight);}}
	  if (btaginfo.TrackPParRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPParRatio().size(); j++) {hist("subTrackPParRatio_b")->Fill(btaginfo.TrackPParRatio().at(j),weight);}}
	  if (btaginfo.TrackJetDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistVal().size(); j++) {hist("subTrackJetDistVal_b")->Fill(btaginfo.TrackJetDistVal().at(j),weight);}}
	  if (btaginfo.TrackJetDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistSig().size(); j++) {hist("subTrackJetDistSig_b")->Fill(btaginfo.TrackJetDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistVal().size(); j++) {hist("subTrackGhostTrackDistVal_b")->Fill(btaginfo.TrackGhostTrackDistVal().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistSig().size(); j++) {hist("subTrackGhostTrackDistSig_b")->Fill(btaginfo.TrackGhostTrackDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackWeight().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackWeight().size(); j++) {hist("subTrackGhostTrackWeight_b")->Fill(btaginfo.TrackGhostTrackWeight().at(j),weight);}}

	  //secondary vertex tag info
	  if (btaginfo.FlightDistance2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dVal().size(); j++) {hist("subFlightDistance2dVal_b")->Fill(btaginfo.FlightDistance2dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dSig().size(); j++) {hist("subFlightDistance2dSig_b")->Fill(btaginfo.FlightDistance2dSig().at(j),weight);}}
	  if (btaginfo.FlightDistance3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dVal().size(); j++) {hist("subFlightDistance3dVal_b")->Fill(btaginfo.FlightDistance3dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dSig().size(); j++) {hist("subFlightDistance3dSig_b")->Fill(btaginfo.FlightDistance3dSig().at(j),weight);}}
	  if (btaginfo.VertexJetDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.VertexJetDeltaR().size(); j++) {hist("subVertexJetDeltaR_b")->Fill(btaginfo.VertexJetDeltaR().at(j),weight);}}
	  hist("subJetNSecondaryVertices_b")->Fill(btaginfo.JetNSecondaryVertices(), weight);
	  if (btaginfo.VertexNTracks().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNTracks().size(); j++) {hist("subVertexNTracks_b")->Fill(btaginfo.VertexNTracks().at(j),weight);}}
	  if (btaginfo.SecondaryVertex().size()>0) {for(unsigned int j=0; j<btaginfo.SecondaryVertex().size(); j++) {hist("subSecondaryVertex_b")->Fill(btaginfo.SecondaryVertex().at(j).M(),weight);}}
	  if (btaginfo.VertexChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexChi2().size(); j++) {hist("subVertexChi2_b")->Fill(btaginfo.VertexChi2().at(j),weight);}}
	  if (btaginfo.VertexNdof().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNdof().size(); j++) {hist("subVertexNdof_b")->Fill(btaginfo.VertexNdof().at(j),weight);}}
	  if (btaginfo.VertexNormalizedChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNormalizedChi2().size(); j++) {hist("subVertexNormalizedChi2_b")->Fill(btaginfo.VertexNormalizedChi2().at(j),weight);}}
 
	  //JTC SV variables
	  hist("subVertexCategoryJTC_b")->Fill(btaginfo.VertexCategoryJTC(), weight);
	  hist("subVertexMassJTC_b")->Fill(btaginfo.VertexMassJTC(), weight);
	  hist("subVertexEnergyRatioJTC_b")->Fill(btaginfo.VertexEnergyRatioJTC(), weight);
	  hist("subTrackSip3dSigAboveCharmJTC_b")->Fill(btaginfo.TrackSip3dSigAboveCharmJTC(), weight);
	} //fill b

      //c
      if (subjet.flavor() == 4 || subjet.flavor()==-4)
	{
	  //btag variables
	  hist("subCSV_c")->Fill(subjet.btag_combinedSecondaryVertex(),weight);
	  hist("subFlavour_c")->Fill(weight);

	  //track impact parameter tag info
	  hist("subTrackMultiplicity_c")->Fill(btaginfo.TrackMomentum().size(), weight);
	  if (btaginfo.TrackMomentum().size()>0) {for(unsigned int j=0; j<btaginfo.TrackMomentum().size(); j++) {hist("subTrackMomentum_c")->Fill(btaginfo.TrackMomentum().at(j),weight);}}
	  if (btaginfo.TrackEta().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEta().size(); j++) {hist("subTrackEta_c")->Fill(btaginfo.TrackEta().at(j),weight);}}
	  if (btaginfo.TrackEtaRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEtaRel().size(); j++) {hist("subTrackEtaRel_c")->Fill(btaginfo.TrackEtaRel().at(j),weight);}}
	  if (btaginfo.TrackDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDeltaR().size(); j++) {hist("subTrackDeltaR_c")->Fill(btaginfo.TrackDeltaR().at(j),weight);}}
 	  if (btaginfo.TrackSip3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dVal().size(); j++) {hist("subTrackSip3dVal_c")->Fill(btaginfo.TrackSip3dVal().at(j),weight);}}
	  if (btaginfo.TrackSip3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dSig().size(); j++) {hist("subTrackSip3dSig_c")->Fill(btaginfo.TrackSip3dSig().at(j),weight);}}
	  if (btaginfo.TrackSip2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dVal().size(); j++) {hist("subTrackSip2dVal_c")->Fill(btaginfo.TrackSip2dVal().at(j),weight);}}
	  if (btaginfo.TrackSip2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dSig().size(); j++) {hist("subTrackSip2dSig_c")->Fill(btaginfo.TrackSip2dSig().at(j),weight);}}
	  if (btaginfo.TrackDecayLenVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDecayLenVal().size(); j++) {hist("subTrackDecayLenVal_c")->Fill(btaginfo.TrackDecayLenVal().at(j),weight);}}
	  if (btaginfo.TrackChi2().size()>0) {for(unsigned int j=0; j<btaginfo.TrackChi2().size(); j++) {hist("subTrackChi2_c")->Fill(btaginfo.TrackChi2().at(j),weight);}}
	  if (btaginfo.TrackNTotalHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNTotalHits().size(); j++) {hist("subTrackNTotalHits_c")->Fill(btaginfo.TrackNTotalHits().at(j),weight);}}
	  if (btaginfo.TrackNPixelHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNPixelHits().size(); j++) {hist("subTrackNPixelHits_c")->Fill(btaginfo.TrackNPixelHits().at(j),weight);}}
	  if (btaginfo.TrackPtRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRel().size(); j++) {hist("subTrackPtRel_c")->Fill(btaginfo.TrackPtRel().at(j),weight);}}
	  if (btaginfo.TrackPPar().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPPar().size(); j++) {hist("subTrackPPar_c")->Fill(btaginfo.TrackPPar().at(j),weight);}}
	  if (btaginfo.TrackPtRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRatio().size(); j++) {hist("subTrackPtRatio_c")->Fill(btaginfo.TrackPtRatio().at(j),weight);}}
	  if (btaginfo.TrackPParRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPParRatio().size(); j++) {hist("subTrackPParRatio_c")->Fill(btaginfo.TrackPParRatio().at(j),weight);}}
	  if (btaginfo.TrackJetDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistVal().size(); j++) {hist("subTrackJetDistVal_c")->Fill(btaginfo.TrackJetDistVal().at(j),weight);}}
	  if (btaginfo.TrackJetDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistSig().size(); j++) {hist("subTrackJetDistSig_c")->Fill(btaginfo.TrackJetDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistVal().size(); j++) {hist("subTrackGhostTrackDistVal_c")->Fill(btaginfo.TrackGhostTrackDistVal().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistSig().size(); j++) {hist("subTrackGhostTrackDistSig_c")->Fill(btaginfo.TrackGhostTrackDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackWeight().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackWeight().size(); j++) {hist("subTrackGhostTrackWeight_c")->Fill(btaginfo.TrackGhostTrackWeight().at(j),weight);}}

	  //secondary vertex tag info
	  if (btaginfo.FlightDistance2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dVal().size(); j++) {hist("subFlightDistance2dVal_c")->Fill(btaginfo.FlightDistance2dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dSig().size(); j++) {hist("subFlightDistance2dSig_c")->Fill(btaginfo.FlightDistance2dSig().at(j),weight);}}
	  if (btaginfo.FlightDistance3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dVal().size(); j++) {hist("subFlightDistance3dVal_c")->Fill(btaginfo.FlightDistance3dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dSig().size(); j++) {hist("subFlightDistance3dSig_c")->Fill(btaginfo.FlightDistance3dSig().at(j),weight);}}
	  if (btaginfo.VertexJetDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.VertexJetDeltaR().size(); j++) {hist("subVertexJetDeltaR_c")->Fill(btaginfo.VertexJetDeltaR().at(j),weight);}}
	  hist("subJetNSecondaryVertices_c")->Fill(btaginfo.JetNSecondaryVertices(), weight);
	  if (btaginfo.VertexNTracks().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNTracks().size(); j++) {hist("subVertexNTracks_c")->Fill(btaginfo.VertexNTracks().at(j),weight);}}
	  if (btaginfo.SecondaryVertex().size()>0) {for(unsigned int j=0; j<btaginfo.SecondaryVertex().size(); j++) {hist("subSecondaryVertex_c")->Fill(btaginfo.SecondaryVertex().at(j).M(),weight);}}
	  if (btaginfo.VertexChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexChi2().size(); j++) {hist("subVertexChi2_c")->Fill(btaginfo.VertexChi2().at(j),weight);}}
	  if (btaginfo.VertexNdof().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNdof().size(); j++) {hist("subVertexNdof_c")->Fill(btaginfo.VertexNdof().at(j),weight);}}
	  if (btaginfo.VertexNormalizedChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNormalizedChi2().size(); j++) {hist("subVertexNormalizedChi2_c")->Fill(btaginfo.VertexNormalizedChi2().at(j),weight);}}

	  //JTC SV variables
	  hist("subVertexCategoryJTC_c")->Fill(btaginfo.VertexCategoryJTC(), weight);
	  hist("subVertexMassJTC_c")->Fill(btaginfo.VertexMassJTC(), weight);
	  hist("subVertexEnergyRatioJTC_c")->Fill(btaginfo.VertexEnergyRatioJTC(), weight);
	  hist("subTrackSip3dSigAboveCharmJTC_c")->Fill(btaginfo.TrackSip3dSigAboveCharmJTC(), weight);
	} //fill c

      //u,d,s
      if (subjet.flavor() == 1 || subjet.flavor()==-1 || subjet.flavor() == 2 || subjet.flavor()==-2 || subjet.flavor() == 3|| subjet.flavor()==-3 )
	{ 
	  //btag variables	
	  hist("subCSV_uds")->Fill(subjet.btag_combinedSecondaryVertex(),weight);
	  hist("subFlavour_uds")->Fill(weight);

	  //track impact parameter tag info
	  hist("subTrackMultiplicity_uds")->Fill(btaginfo.TrackMomentum().size(), weight);
	  if (btaginfo.TrackMomentum().size()>0) {for(unsigned int j=0; j<btaginfo.TrackMomentum().size(); j++) {hist("subTrackMomentum_uds")->Fill(btaginfo.TrackMomentum().at(j),weight);}}
	  if (btaginfo.TrackEta().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEta().size(); j++) {hist("subTrackEta_uds")->Fill(btaginfo.TrackEta().at(j),weight);}}
	  if (btaginfo.TrackEtaRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEtaRel().size(); j++) {hist("subTrackEtaRel_uds")->Fill(btaginfo.TrackEtaRel().at(j),weight);}}
	  if (btaginfo.TrackDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDeltaR().size(); j++) {hist("subTrackDeltaR_uds")->Fill(btaginfo.TrackDeltaR().at(j),weight);}}
	  if (btaginfo.TrackSip3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dVal().size(); j++) {hist("subTrackSip3dVal_uds")->Fill(btaginfo.TrackSip3dVal().at(j),weight);}}
	  if (btaginfo.TrackSip3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dSig().size(); j++) {hist("subTrackSip3dSig_uds")->Fill(btaginfo.TrackSip3dSig().at(j),weight);}}
	  if (btaginfo.TrackSip2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dVal().size(); j++) {hist("subTrackSip2dVal_uds")->Fill(btaginfo.TrackSip2dVal().at(j),weight);}}
	  if (btaginfo.TrackSip2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dSig().size(); j++) {hist("subTrackSip2dSig_uds")->Fill(btaginfo.TrackSip2dSig().at(j),weight);}}
	  if (btaginfo.TrackDecayLenVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDecayLenVal().size(); j++) {hist("subTrackDecayLenVal_uds")->Fill(btaginfo.TrackDecayLenVal().at(j),weight);}}
	  if (btaginfo.TrackChi2().size()>0) {for(unsigned int j=0; j<btaginfo.TrackChi2().size(); j++) {hist("subTrackChi2_uds")->Fill(btaginfo.TrackChi2().at(j),weight);}}
	  if (btaginfo.TrackNTotalHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNTotalHits().size(); j++) {hist("subTrackNTotalHits_uds")->Fill(btaginfo.TrackNTotalHits().at(j),weight);}}
	  if (btaginfo.TrackNPixelHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNPixelHits().size(); j++) {hist("subTrackNPixelHits_uds")->Fill(btaginfo.TrackNPixelHits().at(j),weight);}}
	  if (btaginfo.TrackPtRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRel().size(); j++) {hist("subTrackPtRel_uds")->Fill(btaginfo.TrackPtRel().at(j),weight);}}
	  if (btaginfo.TrackPPar().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPPar().size(); j++) {hist("subTrackPPar_uds")->Fill(btaginfo.TrackPPar().at(j),weight);}}
	  if (btaginfo.TrackPtRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRatio().size(); j++) {hist("subTrackPtRatio_uds")->Fill(btaginfo.TrackPtRatio().at(j),weight);}}
	  if (btaginfo.TrackPParRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPParRatio().size(); j++) {hist("subTrackPParRatio_uds")->Fill(btaginfo.TrackPParRatio().at(j),weight);}}
	  if (btaginfo.TrackJetDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistVal().size(); j++) {hist("subTrackJetDistVal_uds")->Fill(btaginfo.TrackJetDistVal().at(j),weight);}}
	  if (btaginfo.TrackJetDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistSig().size(); j++) {hist("subTrackJetDistSig_uds")->Fill(btaginfo.TrackJetDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistVal().size(); j++) {hist("subTrackGhostTrackDistVal_uds")->Fill(btaginfo.TrackGhostTrackDistVal().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistSig().size(); j++) {hist("subTrackGhostTrackDistSig_uds")->Fill(btaginfo.TrackGhostTrackDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackWeight().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackWeight().size(); j++) {hist("subTrackGhostTrackWeight_uds")->Fill(btaginfo.TrackGhostTrackWeight().at(j),weight);}}

	  //secondary vertex tag info
	  if (btaginfo.FlightDistance2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dVal().size(); j++) {hist("subFlightDistance2dVal_uds")->Fill(btaginfo.FlightDistance2dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dSig().size(); j++) {hist("subFlightDistance2dSig_uds")->Fill(btaginfo.FlightDistance2dSig().at(j),weight);}}
	  if (btaginfo.FlightDistance3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dVal().size(); j++) {hist("subFlightDistance3dVal_uds")->Fill(btaginfo.FlightDistance3dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dSig().size(); j++) {hist("subFlightDistance3dSig_uds")->Fill(btaginfo.FlightDistance3dSig().at(j),weight);}}
	  if (btaginfo.VertexJetDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.VertexJetDeltaR().size(); j++) {hist("subVertexJetDeltaR_uds")->Fill(btaginfo.VertexJetDeltaR().at(j),weight);}}
	  hist("subJetNSecondaryVertices_uds")->Fill(btaginfo.JetNSecondaryVertices(), weight);
	  if (btaginfo.VertexNTracks().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNTracks().size(); j++) {hist("subVertexNTracks_uds")->Fill(btaginfo.VertexNTracks().at(j),weight);}}
	  if (btaginfo.SecondaryVertex().size()>0) {for(unsigned int j=0; j<btaginfo.SecondaryVertex().size(); j++) {hist("subSecondaryVertex_uds")->Fill(btaginfo.SecondaryVertex().at(j).M(),weight);}}
	  if (btaginfo.VertexChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexChi2().size(); j++) {hist("subVertexChi2_uds")->Fill(btaginfo.VertexChi2().at(j),weight);}}
	  if (btaginfo.VertexNdof().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNdof().size(); j++) {hist("subVertexNdof_uds")->Fill(btaginfo.VertexNdof().at(j),weight);}}
	  if (btaginfo.VertexNormalizedChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNormalizedChi2().size(); j++) {hist("subVertexNormalizedChi2_uds")->Fill(btaginfo.VertexNormalizedChi2().at(j),weight);}}

	  //JTC SV variables
	  hist("subVertexCategoryJTC_uds")->Fill(btaginfo.VertexCategoryJTC(), weight);
	  hist("subVertexMassJTC_uds")->Fill(btaginfo.VertexMassJTC(), weight);
	  hist("subVertexEnergyRatioJTC_uds")->Fill(btaginfo.VertexEnergyRatioJTC(), weight);
	  hist("subTrackSip3dSigAboveCharmJTC_uds")->Fill(btaginfo.TrackSip3dSigAboveCharmJTC(), weight);

	} //fill uds

      //gluon    
      if (subjet.flavor() == 21)
	{
	  //btag variables
	  hist("subCSV_g")->Fill(subjet.btag_combinedSecondaryVertex(),weight);
	  hist("subFlavour_g")->Fill(weight);

	  //track impact parameter tag info
	  hist("subTrackMultiplicity_g")->Fill(btaginfo.TrackMomentum().size(), weight);
	  if (btaginfo.TrackMomentum().size()>0) {for(unsigned int j=0; j<btaginfo.TrackMomentum().size(); j++) {hist("subTrackMomentum_g")->Fill(btaginfo.TrackMomentum().at(j),weight);}}
	  if (btaginfo.TrackEta().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEta().size(); j++) {hist("subTrackEta_g")->Fill(btaginfo.TrackEta().at(j),weight);}}
	  if (btaginfo.TrackEtaRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEtaRel().size(); j++) {hist("subTrackEtaRel_g")->Fill(btaginfo.TrackEtaRel().at(j),weight);}}
	  if (btaginfo.TrackDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDeltaR().size(); j++) {hist("subTrackDeltaR_g")->Fill(btaginfo.TrackDeltaR().at(j),weight);}}
	  if (btaginfo.TrackSip3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dVal().size(); j++) {hist("subTrackSip3dVal_g")->Fill(btaginfo.TrackSip3dVal().at(j),weight);}}
	  if (btaginfo.TrackSip3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dSig().size(); j++) {hist("subTrackSip3dSig_g")->Fill(btaginfo.TrackSip3dSig().at(j),weight);}}
	  if (btaginfo.TrackSip2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dVal().size(); j++) {hist("subTrackSip2dVal_g")->Fill(btaginfo.TrackSip2dVal().at(j),weight);}}
	  if (btaginfo.TrackSip2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dSig().size(); j++) {hist("subTrackSip2dSig_g")->Fill(btaginfo.TrackSip2dSig().at(j),weight);}}
	  if (btaginfo.TrackDecayLenVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDecayLenVal().size(); j++) {hist("subTrackDecayLenVal_g")->Fill(btaginfo.TrackDecayLenVal().at(j),weight);}}
	  if (btaginfo.TrackChi2().size()>0) {for(unsigned int j=0; j<btaginfo.TrackChi2().size(); j++) {hist("subTrackChi2_g")->Fill(btaginfo.TrackChi2().at(j),weight);}}
	  if (btaginfo.TrackNTotalHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNTotalHits().size(); j++) {hist("subTrackNTotalHits_g")->Fill(btaginfo.TrackNTotalHits().at(j),weight);}}
	  if (btaginfo.TrackNPixelHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNPixelHits().size(); j++) {hist("subTrackNPixelHits_g")->Fill(btaginfo.TrackNPixelHits().at(j),weight);}}
	  if (btaginfo.TrackPtRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRel().size(); j++) {hist("subTrackPtRel_g")->Fill(btaginfo.TrackPtRel().at(j),weight);}}
	  if (btaginfo.TrackPPar().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPPar().size(); j++) {hist("subTrackPPar_g")->Fill(btaginfo.TrackPPar().at(j),weight);}}
	  if (btaginfo.TrackPtRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRatio().size(); j++) {hist("subTrackPtRatio_g")->Fill(btaginfo.TrackPtRatio().at(j),weight);}}
	  if (btaginfo.TrackPParRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPParRatio().size(); j++) {hist("subTrackPParRatio_g")->Fill(btaginfo.TrackPParRatio().at(j),weight);}}
	  if (btaginfo.TrackJetDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistVal().size(); j++) {hist("subTrackJetDistVal_g")->Fill(btaginfo.TrackJetDistVal().at(j),weight);}}
	  if (btaginfo.TrackJetDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistSig().size(); j++) {hist("subTrackJetDistSig_g")->Fill(btaginfo.TrackJetDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistVal().size(); j++) {hist("subTrackGhostTrackDistVal_g")->Fill(btaginfo.TrackGhostTrackDistVal().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistSig().size(); j++) {hist("subTrackGhostTrackDistSig_g")->Fill(btaginfo.TrackGhostTrackDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackWeight().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackWeight().size(); j++) {hist("subTrackGhostTrackWeight_g")->Fill(btaginfo.TrackGhostTrackWeight().at(j),weight);}}

	  //secondary vertex tag info
	  if (btaginfo.FlightDistance2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dVal().size(); j++) {hist("subFlightDistance2dVal_g")->Fill(btaginfo.FlightDistance2dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dSig().size(); j++) {hist("subFlightDistance2dSig_g")->Fill(btaginfo.FlightDistance2dSig().at(j),weight);}}
	  if (btaginfo.FlightDistance3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dVal().size(); j++) {hist("subFlightDistance3dVal_g")->Fill(btaginfo.FlightDistance3dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dSig().size(); j++) {hist("subFlightDistance3dSig_g")->Fill(btaginfo.FlightDistance3dSig().at(j),weight);}}
	  if (btaginfo.VertexJetDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.VertexJetDeltaR().size(); j++) {hist("subVertexJetDeltaR_g")->Fill(btaginfo.VertexJetDeltaR().at(j),weight);}}
	  hist("subJetNSecondaryVertices_g")->Fill(btaginfo.JetNSecondaryVertices(), weight);
	  if (btaginfo.VertexNTracks().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNTracks().size(); j++) {hist("subVertexNTracks_g")->Fill(btaginfo.VertexNTracks().at(j),weight);}}
	  if (btaginfo.SecondaryVertex().size()>0) {for(unsigned int j=0; j<btaginfo.SecondaryVertex().size(); j++) {hist("subSecondaryVertex_g")->Fill(btaginfo.SecondaryVertex().at(j).M(),weight);}}
	  if (btaginfo.VertexChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexChi2().size(); j++) {hist("subVertexChi2_g")->Fill(btaginfo.VertexChi2().at(j),weight);}}
	  if (btaginfo.VertexNdof().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNdof().size(); j++) {hist("subVertexNdof_g")->Fill(btaginfo.VertexNdof().at(j),weight);}}
	  if (btaginfo.VertexNormalizedChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNormalizedChi2().size(); j++) {hist("subVertexNormalizedChi2_g")->Fill(btaginfo.VertexNormalizedChi2().at(j),weight);}}

	  //JTC SV variables
	  hist("subVertexCategoryJTC_g")->Fill(btaginfo.VertexCategoryJTC(), weight);
	  hist("subVertexMassJTC_g")->Fill(btaginfo.VertexMassJTC(), weight);
	  hist("subVertexEnergyRatioJTC_g")->Fill(btaginfo.VertexEnergyRatioJTC(), weight);
	  hist("subTrackSip3dSigAboveCharmJTC_g")->Fill(btaginfo.TrackSip3dSigAboveCharmJTC(), weight);
	} //fill g
       
      //none
      if (subjet.flavor() == 0)
	{
	  //btag variables
	  hist("subCSV_none")->Fill(subjet.btag_combinedSecondaryVertex(),weight);
	  hist("subFlavour_none")->Fill(weight);

	  //track impact parameter tag info
	  hist("subTrackMultiplicity_none")->Fill(btaginfo.TrackMomentum().size(), weight);
	  if (btaginfo.TrackMomentum().size()>0) {for(unsigned int j=0; j<btaginfo.TrackMomentum().size(); j++) {hist("subTrackMomentum_none")->Fill(btaginfo.TrackMomentum().at(j),weight);}}
	  if (btaginfo.TrackEta().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEta().size(); j++) {hist("subTrackEta_none")->Fill(btaginfo.TrackEta().at(j),weight);}}
	  if (btaginfo.TrackEtaRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackEtaRel().size(); j++) {hist("subTrackEtaRel_none")->Fill(btaginfo.TrackEtaRel().at(j),weight);}}
	  if (btaginfo.TrackDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDeltaR().size(); j++) {hist("subTrackDeltaR_none")->Fill(btaginfo.TrackDeltaR().at(j),weight);}}
	  if (btaginfo.TrackSip3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dVal().size(); j++) {hist("subTrackSip3dVal_none")->Fill(btaginfo.TrackSip3dVal().at(j),weight);}}
	  if (btaginfo.TrackSip3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip3dSig().size(); j++) {hist("subTrackSip3dSig_none")->Fill(btaginfo.TrackSip3dSig().at(j),weight);}}
	  if (btaginfo.TrackSip2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dVal().size(); j++) {hist("subTrackSip2dVal_none")->Fill(btaginfo.TrackSip2dVal().at(j),weight);}}
	  if (btaginfo.TrackSip2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackSip2dSig().size(); j++) {hist("subTrackSip2dSig_none")->Fill(btaginfo.TrackSip2dSig().at(j),weight);}}
	  if (btaginfo.TrackDecayLenVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackDecayLenVal().size(); j++) {hist("subTrackDecayLenVal_none")->Fill(btaginfo.TrackDecayLenVal().at(j),weight);}}
	  if (btaginfo.TrackChi2().size()>0) {for(unsigned int j=0; j<btaginfo.TrackChi2().size(); j++) {hist("subTrackChi2_none")->Fill(btaginfo.TrackChi2().at(j),weight);}}
	  if (btaginfo.TrackNTotalHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNTotalHits().size(); j++) {hist("subTrackNTotalHits_none")->Fill(btaginfo.TrackNTotalHits().at(j),weight);}}
	  if (btaginfo.TrackNPixelHits().size()>0) {for(unsigned int j=0; j<btaginfo.TrackNPixelHits().size(); j++) {hist("subTrackNPixelHits_none")->Fill(btaginfo.TrackNPixelHits().at(j),weight);}}
	  if (btaginfo.TrackPtRel().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRel().size(); j++) {hist("subTrackPtRel_none")->Fill(btaginfo.TrackPtRel().at(j),weight);}}
	  if (btaginfo.TrackPPar().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPPar().size(); j++) {hist("subTrackPPar_none")->Fill(btaginfo.TrackPPar().at(j),weight);}}
	  if (btaginfo.TrackPtRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPtRatio().size(); j++) {hist("subTrackPtRatio_none")->Fill(btaginfo.TrackPtRatio().at(j),weight);}}
	  if (btaginfo.TrackPParRatio().size()>0) {for(unsigned int j=0; j<btaginfo.TrackPParRatio().size(); j++) {hist("subTrackPParRatio_none")->Fill(btaginfo.TrackPParRatio().at(j),weight);}}
	  if (btaginfo.TrackJetDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistVal().size(); j++) {hist("subTrackJetDistVal_none")->Fill(btaginfo.TrackJetDistVal().at(j),weight);}}
	  if (btaginfo.TrackJetDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackJetDistSig().size(); j++) {hist("subTrackJetDistSig_none")->Fill(btaginfo.TrackJetDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackDistVal().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistVal().size(); j++) {hist("subTrackGhostTrackDistVal_none")->Fill(btaginfo.TrackGhostTrackDistVal().at(j),weight);}}  
	  if (btaginfo.TrackGhostTrackDistSig().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackDistSig().size(); j++) {hist("subTrackGhostTrackDistSig_none")->Fill(btaginfo.TrackGhostTrackDistSig().at(j),weight);}}
	  if (btaginfo.TrackGhostTrackWeight().size()>0) {for(unsigned int j=0; j<btaginfo.TrackGhostTrackWeight().size(); j++) {hist("subTrackGhostTrackWeight_none")->Fill(btaginfo.TrackGhostTrackWeight().at(j),weight);}}

	  //secondary vertex tag info
	  if (btaginfo.FlightDistance2dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dVal().size(); j++) {hist("subFlightDistance2dVal_none")->Fill(btaginfo.FlightDistance2dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance2dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance2dSig().size(); j++) {hist("subFlightDistance2dSig_none")->Fill(btaginfo.FlightDistance2dSig().at(j),weight);}}
	  if (btaginfo.FlightDistance3dVal().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dVal().size(); j++) {hist("subFlightDistance3dVal_none")->Fill(btaginfo.FlightDistance3dVal().at(j),weight);}}
	  if (btaginfo.FlightDistance3dSig().size()>0) {for(unsigned int j=0; j<btaginfo.FlightDistance3dSig().size(); j++) {hist("subFlightDistance3dSig_none")->Fill(btaginfo.FlightDistance3dSig().at(j),weight);}}
	  if (btaginfo.VertexJetDeltaR().size()>0) {for(unsigned int j=0; j<btaginfo.VertexJetDeltaR().size(); j++) {hist("subVertexJetDeltaR_none")->Fill(btaginfo.VertexJetDeltaR().at(j),weight);}}
	  hist("subJetNSecondaryVertices_none")->Fill(btaginfo.JetNSecondaryVertices(), weight);
	  if (btaginfo.VertexNTracks().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNTracks().size(); j++) {hist("subVertexNTracks_none")->Fill(btaginfo.VertexNTracks().at(j),weight);}}
	  if (btaginfo.SecondaryVertex().size()>0) {for(unsigned int j=0; j<btaginfo.SecondaryVertex().size(); j++) {hist("subSecondaryVertex_none")->Fill(btaginfo.SecondaryVertex().at(j).M(),weight);}}
	  if (btaginfo.VertexChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexChi2().size(); j++) {hist("subVertexChi2_none")->Fill(btaginfo.VertexChi2().at(j),weight);}}
	  if (btaginfo.VertexNdof().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNdof().size(); j++) {hist("subVertexNdof_none")->Fill(btaginfo.VertexNdof().at(j),weight);}}
	  if (btaginfo.VertexNormalizedChi2().size()>0) {for(unsigned int j=0; j<btaginfo.VertexNormalizedChi2().size(); j++) {hist("subVertexNormalizedChi2_none")->Fill(btaginfo.VertexNormalizedChi2().at(j),weight);}}

	  //JTC SV variables
	  hist("subVertexCategoryJTC_none")->Fill(btaginfo.VertexCategoryJTC(), weight);
	  hist("subVertexMassJTC_none")->Fill(btaginfo.VertexMassJTC(), weight);
	  hist("subVertexEnergyRatioJTC_none")->Fill(btaginfo.VertexEnergyRatioJTC(), weight);
	  hist("subTrackSip3dSigAboveCharmJTC_none")->Fill(btaginfo.TrackSip3dSigAboveCharmJTC(), weight);


	} // Fill none
    } //loop over subjets
    hist("subjetPT")->Fill(PT, weight);
    hist("subjethadronFlavor")->Fill(flavor, weight);
    if (flavor == 5) hist("subjetPT_b")->Fill(PT, weight);
    if (flavor == 4) hist("subjetPT_c")->Fill(PT, weight);
    if (flavor != 5 && flavor !=4) hist("subjetPT_udsg")->Fill(PT, weight);


  }  //loop over topjets 
}

Hists_sub::~Hists_sub(){}
