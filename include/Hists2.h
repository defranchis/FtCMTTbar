#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "UHH2/common/include/ObjectIdUtils.h"


namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class Hists2: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    Hists2(uhh2::Context & ctx, const std::string & dirname);
    
    virtual void fill(const uhh2::Event & ev) override;
    virtual ~Hists2();

private:
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetsCMSTopTag;
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetssoftdrop;
    std::unique_ptr<FactorizedJetCorrector> jecAK8_;


};

}
