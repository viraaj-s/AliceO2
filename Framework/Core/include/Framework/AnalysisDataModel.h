// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
#ifndef O2_FRAMEWORK_ANALYSISDATAMODEL_H_
#define O2_FRAMEWORK_ANALYSISDATAMODEL_H_

#include "Framework/ASoA.h"
#include "MathUtils/Utils.h"
#include <cmath>

namespace o2
{
namespace aod
{
// This is required to register SOA_TABLEs inside
// the o2::aod namespace.
DECLARE_SOA_STORE();

namespace collision
{
// DECLARE_SOA_COLUMN(TimeframeId, timeframeId, uint64_t);
DECLARE_SOA_COLUMN(RunNumber, runNumber, int);
DECLARE_SOA_COLUMN(GlobalBC, globalBC, uint64_t);
DECLARE_SOA_COLUMN_FULL(PosX, posX, float, "fX");
DECLARE_SOA_COLUMN_FULL(PosY, posY, float, "fY");
DECLARE_SOA_COLUMN_FULL(PosZ, posZ, float, "fZ");
DECLARE_SOA_COLUMN(CovXX, covXX, float);
DECLARE_SOA_COLUMN(CovXY, covXY, float);
DECLARE_SOA_COLUMN(CovXZ, covXZ, float);
DECLARE_SOA_COLUMN(CovYY, covYY, float);
DECLARE_SOA_COLUMN(CovYZ, covYZ, float);
DECLARE_SOA_COLUMN(CovZZ, covZZ, float);
DECLARE_SOA_COLUMN(Chi2, chi2, float);
DECLARE_SOA_COLUMN_FULL(NumContrib, numContrib, uint32_t, "fN");
DECLARE_SOA_COLUMN(CollisionTime, collisionTime, float);
DECLARE_SOA_COLUMN(CollisionTimeRes, collisionTimeRes, float);
DECLARE_SOA_COLUMN(CollisionTimeMask, collisionTimeMask, uint8_t);
} // namespace collision

DECLARE_SOA_TABLE(Collisions, "AOD", "COLLISION", o2::soa::Index<>, collision::RunNumber, collision::GlobalBC, collision::PosX, collision::PosY, collision::PosZ, collision::CovXX, collision::CovXY, collision::CovXZ, collision::CovYY, collision::CovYZ, collision::CovZZ, collision::Chi2, collision::NumContrib, collision::CollisionTime, collision::CollisionTimeRes, collision::CollisionTimeMask);

using Collision = Collisions::iterator;

namespace track
{
// TRACKPAR TABLE definition
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN(X, x, float);
DECLARE_SOA_COLUMN(Alpha, alpha, float);
DECLARE_SOA_COLUMN(Y, y, float);
DECLARE_SOA_COLUMN(Z, z, float);
DECLARE_SOA_COLUMN(Snp, snp, float);
DECLARE_SOA_COLUMN(Tgl, tgl, float);
DECLARE_SOA_COLUMN(Signed1Pt, signed1Pt, float);
DECLARE_SOA_DYNAMIC_COLUMN(Phi, phi, [](float snp, float alpha) -> float { return asinf(snp) + alpha + static_cast<float>(M_PI); });
DECLARE_SOA_DYNAMIC_COLUMN(Eta, eta, [](float tgl) -> float { return logf(tanf(0.25f * static_cast<float>(M_PI) - 0.5f * atanf(tgl))); });
DECLARE_SOA_DYNAMIC_COLUMN(Pt, pt, [](float signed1Pt) -> float { return std::abs(1.0f / signed1Pt); });
DECLARE_SOA_DYNAMIC_COLUMN(Charge, charge, [](float signed1Pt) -> short { return (signed1Pt > 0) ? 1 : -1; });
DECLARE_SOA_DYNAMIC_COLUMN(Px, px, [](float signed1Pt, float snp, float alpha) -> float {
  auto pt = 1.f / std::abs(signed1Pt);
  float cs, sn;
  utils::sincosf(alpha, sn, cs);
  auto r = std::sqrt((1.f - snp) * (1.f + snp));
  return pt * (r * cs - snp * sn);
});
DECLARE_SOA_DYNAMIC_COLUMN(Py, py, [](float signed1Pt, float snp, float alpha) -> float {
  auto pt = 1.f / std::abs(signed1Pt);
  float cs, sn;
  utils::sincosf(alpha, sn, cs);
  auto r = std::sqrt((1.f - snp) * (1.f + snp));
  return pt * (snp * cs + r * sn);
});
DECLARE_SOA_DYNAMIC_COLUMN(Pz, pz, [](float signed1Pt, float tgl) -> float {
  auto pt = 1.f / std::abs(signed1Pt);
  return pt * tgl;
});
DECLARE_SOA_DYNAMIC_COLUMN(P, p, [](float signed1Pt, float tgl) -> float {
  return std::sqrt(1.f + tgl * tgl) / std::abs(signed1Pt);
});
DECLARE_SOA_DYNAMIC_COLUMN(P2, p2, [](float signed1Pt, float tgl) -> float {
  return (1.f + tgl * tgl) / (signed1Pt * signed1Pt);
});

// TRACKPARCOV TABLE definition
DECLARE_SOA_COLUMN(CYY, cYY, float);
DECLARE_SOA_COLUMN(CZY, cZY, float);
DECLARE_SOA_COLUMN(CZZ, cZZ, float);
DECLARE_SOA_COLUMN(CSnpY, cSnpY, float);
DECLARE_SOA_COLUMN(CSnpZ, cSnpZ, float);
DECLARE_SOA_COLUMN(CSnpSnp, cSnpSnp, float);
DECLARE_SOA_COLUMN(CTglY, cTglY, float);
DECLARE_SOA_COLUMN(CTglZ, cTglZ, float);
DECLARE_SOA_COLUMN(CTglSnp, cTglSnp, float);
DECLARE_SOA_COLUMN(CTglTgl, cTglTgl, float);
DECLARE_SOA_COLUMN(C1PtY, c1PtY, float);
DECLARE_SOA_COLUMN(C1PtZ, c1PtZ, float);
DECLARE_SOA_COLUMN(C1PtSnp, c1PtSnp, float);
DECLARE_SOA_COLUMN(C1PtTgl, c1PtTgl, float);
DECLARE_SOA_COLUMN(C1Pt21Pt2, c1Pt21Pt2, float);

// TRACKEXTRA TABLE definition
DECLARE_SOA_COLUMN_FULL(TPCInnerParam, tpcInnerParam, float, "fTPCinnerP");
DECLARE_SOA_COLUMN(Flags, flags, uint64_t);
DECLARE_SOA_COLUMN_FULL(ITSClusterMap, itsClusterMap, uint8_t, "fITSClusterMap");
DECLARE_SOA_COLUMN_FULL(TPCNClsFindable, tpcNClsFindable, uint8_t, "fTPCnclsFindable");
DECLARE_SOA_COLUMN_FULL(TPCNClsFindableMinusFound, tpcNClsFindableMinusFound, int8_t, "fTPCnclsFindableMinusFound");
DECLARE_SOA_COLUMN_FULL(TPCNClsFindableMinusCrossedRows, tpcNClsFindableMinusCrossedRows, int8_t, "fTPCnclsFindableMinusCrossedRows");
DECLARE_SOA_COLUMN_FULL(TPCNClsShared, tpcNClsShared, uint8_t, "fTPCnclsShared");
DECLARE_SOA_COLUMN_FULL(TRDNTracklets, trdNTracklets, uint8_t, "fTRDntracklets");
DECLARE_SOA_COLUMN_FULL(ITSChi2NCl, itsChi2NCl, float, "fITSchi2Ncl");
DECLARE_SOA_COLUMN(TPCchi2Ncl, tpcChi2Ncl, float);
DECLARE_SOA_COLUMN(TRDchi2, trdChi2, float);
DECLARE_SOA_COLUMN(TOFchi2, tofChi2, float);
DECLARE_SOA_COLUMN(TPCsignal, tpcSignal, float);
DECLARE_SOA_COLUMN(TRDsignal, trdSignal, float);
DECLARE_SOA_COLUMN(TOFsignal, tofSignal, float);
DECLARE_SOA_COLUMN(Length, length, float);
DECLARE_SOA_DYNAMIC_COLUMN(TPCNClsFound, tpcNClsFound, [](uint8_t tpcNClsFindable, uint8_t tpcNClsFindableMinusFound) -> int16_t { return tpcNClsFindable - tpcNClsFindableMinusFound; });
DECLARE_SOA_DYNAMIC_COLUMN(TPCNClsCrossedRows, tpcNClsCrossedRows, [](uint8_t tpcNClsFindable, uint8_t TPCNClsFindableMinusCrossedRows) -> int16_t { return tpcNClsFindable - TPCNClsFindableMinusCrossedRows; });

DECLARE_SOA_DYNAMIC_COLUMN(ITSNCls, itsNCls, [](uint8_t itsClusterMap) -> uint8_t {
  uint8_t itsNcls = 0;
  constexpr uint8_t bit = 1;
  for (int layer = 0; layer < 7; layer++)
    if (itsClusterMap & (bit << layer))
      itsNcls++;
  return itsNcls;
});

DECLARE_SOA_DYNAMIC_COLUMN(TPCCrossedRowsOverFindableCls, tpcCrossedRowsOverFindableCls,
                           [](uint8_t tpcNClsFindable, uint8_t tpcNClsFindableMinusCrossedRows) -> float {
                             // FIXME: use int16 tpcNClsCrossedRows from dynamic column as argument
                             int16_t tpcNClsCrossedRows = tpcNClsFindable - tpcNClsFindableMinusCrossedRows;
                             return (float)tpcNClsCrossedRows / (float)tpcNClsFindable;
                             ;
                           });

DECLARE_SOA_DYNAMIC_COLUMN(TPCFractionSharedCls, tpcFractionSharedCls, [](uint8_t tpcNClsShared, uint8_t tpcNClsFindable, uint8_t tpcNClsFindableMinusFound) -> float {
  // FIXME: use tpcNClsFound from dynamic column as argument
  int16_t tpcNClsFound = tpcNClsFindable - tpcNClsFindableMinusFound;
  return (float)tpcNClsShared / (float)tpcNClsFound;
});
} // namespace track

DECLARE_SOA_TABLE(Tracks, "AOD", "TRACKPAR",
                  o2::soa::Index<>, track::CollisionId, track::X, track::Alpha,
                  track::Y, track::Z, track::Snp, track::Tgl,
                  track::Signed1Pt,
                  track::Phi<track::Snp, track::Alpha>,
                  track::Eta<track::Tgl>,
                  track::Pt<track::Signed1Pt>,
                  track::Px<track::Signed1Pt, track::Snp, track::Alpha>,
                  track::Py<track::Signed1Pt, track::Snp, track::Alpha>,
                  track::Pz<track::Signed1Pt, track::Tgl>,
                  track::P<track::Signed1Pt, track::Tgl>,
                  track::P2<track::Signed1Pt, track::Tgl>,
                  track::Charge<track::Signed1Pt>);

DECLARE_SOA_TABLE(TracksCov, "AOD", "TRACKPARCOV",
                  track::CYY, track::CZY, track::CZZ, track::CSnpY,
                  track::CSnpZ, track::CSnpSnp, track::CTglY,
                  track::CTglZ, track::CTglSnp, track::CTglTgl,
                  track::C1PtY, track::C1PtZ, track::C1PtSnp, track::C1PtTgl,
                  track::C1Pt21Pt2);

DECLARE_SOA_TABLE(TracksExtra, "AOD", "TRACKEXTRA",
                  track::TPCInnerParam, track::Flags, track::ITSClusterMap,
                  track::TPCNClsFindable, track::TPCNClsFindableMinusFound, track::TPCNClsFindableMinusCrossedRows,
                  track::TPCNClsShared, track::TRDNTracklets, track::ITSChi2NCl,
                  track::TPCchi2Ncl, track::TRDchi2, track::TOFchi2,
                  track::TPCsignal, track::TRDsignal, track::TOFsignal, track::Length,
                  track::TPCNClsFound<track::TPCNClsFindable, track::TPCNClsFindableMinusFound>,
                  track::TPCNClsCrossedRows<track::TPCNClsFindable, track::TPCNClsFindableMinusCrossedRows>,
                  track::ITSNCls<track::ITSClusterMap>,
                  track::TPCCrossedRowsOverFindableCls<track::TPCNClsFindable, track::TPCNClsFindableMinusCrossedRows>,
                  track::TPCFractionSharedCls<track::TPCNClsShared, track::TPCNClsFindable, track::TPCNClsFindableMinusFound>);

using Track = Tracks::iterator;
using TrackCov = TracksCov::iterator;
using TrackExtra = TracksExtra::iterator;

namespace unassignedtracks
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_INDEX_COLUMN(Track, track);
} // namespace unassignedtracks

DECLARE_SOA_TABLE(UnassignedTracks, "AOD", "UNASSIGNEDTRACK",
                  unassignedtracks::CollisionId, unassignedtracks::TrackId);

using UnassignedTrack = UnassignedTracks::iterator;

namespace calo
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN(CellNumber, cellNumber, int16_t);
DECLARE_SOA_COLUMN(Amplitude, amplitude, float);
DECLARE_SOA_COLUMN(Time, time, float);
DECLARE_SOA_COLUMN(CellType, cellType, int8_t);
DECLARE_SOA_COLUMN_FULL(CaloType, caloType, int8_t, "fType");
} // namespace calo

DECLARE_SOA_TABLE(Calos, "AOD", "CALO",
                  calo::CollisionId, calo::CellNumber, calo::Amplitude, calo::Time, calo::CellType, calo::CaloType);
using Calo = Calos::iterator;

namespace calotrigger
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN_FULL(FastorAbsId, fastorAbsId, int32_t, "fFastorAbsID");
DECLARE_SOA_COLUMN(L0Amplitude, l0Amplitude, float);
DECLARE_SOA_COLUMN(L0Time, l0Time, float);
DECLARE_SOA_COLUMN_FULL(L1Timesum, l1Timesum, int32_t, "fL1TimeSum");
DECLARE_SOA_COLUMN(NL0Times, nl0Times, int8_t);
DECLARE_SOA_COLUMN_FULL(Triggerbits, triggerbits, int32_t, "fTriggerBits");
DECLARE_SOA_COLUMN_FULL(CaloType, caloType, int8_t, "fType");
} // namespace calotrigger

DECLARE_SOA_TABLE(CaloTriggers, "AOD", "CALOTRIGGER",
                  calotrigger::CollisionId, calotrigger::FastorAbsId, calotrigger::L0Amplitude, calotrigger::L0Time, calotrigger::L1Timesum, calotrigger::NL0Times, calotrigger::Triggerbits, calotrigger::CaloType);
using CaloTrigger = CaloTriggers::iterator;

namespace muon
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN(InverseBendingMomentum, inverseBendingMomentum, float);
DECLARE_SOA_COLUMN(ThetaX, thetaX, float);
DECLARE_SOA_COLUMN(ThetaY, thetaY, float);
DECLARE_SOA_COLUMN_FULL(ZMu, zMu, float, "fZ");
DECLARE_SOA_COLUMN(BendingCoor, bendingCoor, float);
DECLARE_SOA_COLUMN(NonBendingCoor, nonBendingCoor, float);
// FIXME: need to implement array columns...
// DECLARE_SOA_COLUMN(Covariances, covariances, float[], "fCovariances");
DECLARE_SOA_COLUMN(Chi2, chi2, float);
DECLARE_SOA_COLUMN(Chi2MatchTrigger, chi2MatchTrigger, float);
} // namespace muon

DECLARE_SOA_TABLE(Muons, "AOD", "MUON",
                  muon::CollisionId, muon::InverseBendingMomentum,
                  muon::ThetaX, muon::ThetaY, muon::ZMu,
                  muon::BendingCoor, muon::NonBendingCoor,
                  muon::Chi2, muon::Chi2MatchTrigger);
using Muon = Muons::iterator;

namespace muoncluster
{
/// FIXME: where does this point to???? Tracks or Muons?
DECLARE_SOA_INDEX_COLUMN_FULL(Track, track, int, Muons, "fMuonsID");
DECLARE_SOA_COLUMN(X, x, float);
DECLARE_SOA_COLUMN(Y, y, float);
DECLARE_SOA_COLUMN(Z, z, float);
DECLARE_SOA_COLUMN(ErrX, errX, float);
DECLARE_SOA_COLUMN(ErrY, errY, float);
DECLARE_SOA_COLUMN(Charge, charge, float);
DECLARE_SOA_COLUMN(Chi2, chi2, float);
} // namespace muoncluster

DECLARE_SOA_TABLE(MuonClusters, "AOD", "MUONCLUSTER",
                  muoncluster::TrackId,
                  muoncluster::X, muoncluster::Y, muoncluster::Z,
                  muoncluster::ErrX, muoncluster::ErrY,
                  muoncluster::Charge, muoncluster::Chi2);

using MuonCluster = MuonClusters::iterator;

namespace zdc
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN(ZEM1Energy, zem1Energy, float);
DECLARE_SOA_COLUMN(ZEM2Energy, zem2Energy, float);
DECLARE_SOA_COLUMN(ZNCTowerEnergy, zncTowerEnergy, float[5]);
DECLARE_SOA_COLUMN(ZNATowerEnergy, znaTowerEnergy, float[5]);
DECLARE_SOA_COLUMN(ZPCTowerEnergy, zpcTowerEnergy, float[5]);
DECLARE_SOA_COLUMN(ZPATowerEnergy, zpaTowerEnergy, float[5]);
DECLARE_SOA_COLUMN(ZNCTowerEnergyLR, zncTowerEnergyLR, float[5]);
DECLARE_SOA_COLUMN(ZNATowerEnergyLR, znaTowerEnergyLR, float[5]);
DECLARE_SOA_COLUMN(ZPCTowerEnergyLR, zpcTowerEnergyLR, float[5]);
DECLARE_SOA_COLUMN(ZPATowerEnergyLR, zpaTowerEnergyLR, float[5]);
//DECLARE_SOA_COLUMN(fZDCTDCCorrected, fZDCTDCCorrected, float[32][4]);
DECLARE_SOA_COLUMN(Fired, fired, uint8_t);
} // namespace zdc

DECLARE_SOA_TABLE(Zdcs, "AOD", "ZDC", zdc::CollisionId,
                  zdc::ZEM1Energy, zdc::ZEM2Energy,
                  zdc::ZNCTowerEnergy, zdc::ZNATowerEnergy, zdc::ZPCTowerEnergy, zdc::ZPATowerEnergy,
                  zdc::ZNCTowerEnergyLR, zdc::ZNATowerEnergyLR, zdc::ZPCTowerEnergyLR, zdc::ZPATowerEnergyLR,
                  zdc::Fired);
using Zdc = Zdcs::iterator;

namespace vzero
{
DECLARE_SOA_INDEX_COLUMN(Collision, collision);
DECLARE_SOA_COLUMN(Adc, adc, float[64]);
DECLARE_SOA_COLUMN(Time, time, float[64]);
DECLARE_SOA_COLUMN(Width, width, float[64]);
DECLARE_SOA_COLUMN(BBFlag, bbFlag, uint64_t);
DECLARE_SOA_COLUMN(BGFlag, bgFlag, uint64_t);
} // namespace vzero

DECLARE_SOA_TABLE(VZeros, "AOD", "VZERO", vzero::CollisionId,
                  vzero::Adc, vzero::Time, vzero::Width,
                  vzero::BBFlag, vzero::BGFlag);
using VZero = VZeros::iterator;

namespace v0
{
DECLARE_SOA_INDEX_COLUMN_FULL(PosTrack, posTrack, int, Tracks, "fPosTrackID");
DECLARE_SOA_INDEX_COLUMN_FULL(NegTrack, negTrack, int, Tracks, "fNegTrackID");
} // namespace v0

DECLARE_SOA_TABLE(V0s, "AOD", "V0", v0::PosTrackId, v0::NegTrackId);
using V0 = V0s::iterator;

namespace cascade
{
DECLARE_SOA_INDEX_COLUMN(V0, v0);
DECLARE_SOA_INDEX_COLUMN_FULL(Bachelor, bachelor, int, Tracks, "fTracksID");
} // namespace cascade

DECLARE_SOA_TABLE(Cascades, "AOD", "CASCADE", cascade::V0Id, cascade::BachelorId);
using Casecade = Cascades::iterator;

namespace trigger
{
DECLARE_SOA_COLUMN(GlobalBC, globalBC, uint64_t);
DECLARE_SOA_COLUMN(TriggerMask, triggerMask, uint64_t);
} // namespace trigger

DECLARE_SOA_TABLE(Triggers, "AOD", "TRIGGER", trigger::TriggerMask, trigger::GlobalBC);
using Trigger = Triggers::iterator;

namespace timeframe
{
DECLARE_SOA_COLUMN(Timestamp, timestamp, uint64_t);
} // namespace timeframe

DECLARE_SOA_TABLE(Timeframes, "AOD", "TIMEFRAME",
                  timeframe::Timestamp);
using Timeframe = Timeframes::iterator;

} // namespace aod

} // namespace o2
#endif // O2_FRAMEWORK_ANALYSISDATAMODEL_H_
