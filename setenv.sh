module use -a /afs/desy.de/group/cms/modulefiles/
module load cmssw
module load root

cd /nfs/dust/cms/user/schumas/sframev4/SFramePhys14/
source setup.sh
cd /nfs/dust/cms/user/schumas/sframev4/CMSSW_7_4_15_patch1/src/
cmsenv
cd UHH2/
export TMPDIR="/nfs/dust/cms/user/schumas/tmp/"


