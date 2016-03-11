module use -a /afs/desy.de/group/cms/modulefiles/
module load cmssw
module load root

cd ../../../../SFramePhys14/
source setup.sh
cd ../CMSSW_7_6_3/src/
cmsenv
cd UHH2/
export TMPDIR="/nfs/dust/cms/user/schumas/tmp/"


