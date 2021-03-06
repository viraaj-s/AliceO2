#!/bin/bash
SHA256_ATTEMPTS="16 12 8 6 4 2 1"
FILELIST=~/src/data/filelist.txt
DATE=`date +%Y-%m-%d`
HOST=`hostname -s`
FILES=`cat $FILELIST | wc -l`
FILES_SIZE=$(du -cm `cat ~/src/data/filelist.txt` | tail -n 1 | awk '{print $1}')

for x in $SHA256_ATTEMPTS; do
  T=`(time -p (cat $FILELIST | xargs -P $x -n1 -I{} sha256sum {} >&2)) 2>&1 | grep real | sed -e 's/real //'`
  TP=$(bc -l <<< "scale=2; $FILES_SIZE/$T")
  TPP=$(bc -l <<< "scale=2; $FILES_SIZE/$T/$x")
  echo sha256sum,$x,$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST
done

BENCHMARK=stage/bin/o2-analysistutorial-histograms
HISTO_ATTEMPTS="16 8 4 2 1"
for x in $HISTO_ATTEMPTS ; do
  T=`(time -p $BENCHMARK -b --aod-file @$FILELIST --pipeline eta-and-phi-histograms:1,pt-histogram:1,etaphi-histogram:1 --readers $x > log$x.txt) 2>&1 | grep real | sed -e 's/real //'`
  TP=$(bc -l <<< "scale=2; $FILES_SIZE/$T")
  TPP=$(bc -l <<< "scale=2; $FILES_SIZE/$T/$x")
  echo "histo (readers),$x,$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
  echo "histo (total),$(($x + 4 )),$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
done

BENCHMARK=stage/bin/o2-analysistutorial-histograms
HISTO_ATTEMPTS="16 8 4 2 1"
for x in $HISTO_ATTEMPTS ; do
  T=`(time -p $BENCHMARK -b --aod-file @$FILELIST --pipeline eta-and-phi-histograms:2,pt-histogram:2,etaphi-histogram:2 --readers $x > log$x.txt) 2>&1 | grep real | sed -e 's/real //'`
  TP=$(bc -l <<< "scale=2; $FILES_SIZE/$T")
  TPP=$(bc -l <<< "scale=2; $FILES_SIZE/$T/$x")
  echo "histo with 2 jobs (readers),$x,$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
  echo "histo with 2 jobs (total),$(($x + 7 )),$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
done

BENCHMARK=stage/bin/o2-analysis-vertexing-hf
HISTO_ATTEMPTS="8 4 2 1"
for x in $HISTO_ATTEMPTS ; do
  echo $BENCHMARK -b --aod-file @$FILELIST --pipeline vertexerhf-candidatebuildingDzero:2,vertexerhf-decayvertexbuilder2prong:2 --readers $x > log$x.txt >&2
  TP=$(bc -l <<< "scale=2; $FILES_SIZE/$T")
  TPP=$(bc -l <<< "scale=2; $FILES_SIZE/$T/$x")
  T=`(time -p $BENCHMARK --aod-file @$FILELIST -q --pipeline vertexerhf-candidatebuildingDzero:2,vertexerhf-decayvertexbuilder2prong:2 --readers $x > log$x.txt) 2>&1 | grep real | sed -e 's/real //'`
  echo "o2-analysis-vertexing-hf with 2 jobs (readers),$x,$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
  echo "o2-analysis-vertexing-hf (total),$(($x + 6)),$T,$FILES_SIZE,$FILES,$TP,$TPP,$DATE,$HOST"
done
