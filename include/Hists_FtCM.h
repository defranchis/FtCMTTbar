#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class Hists_FtCM: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    Hists_FtCM(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;
    virtual ~Hists_FtCM();

private:
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetsCMSTopTag;
    uhh2::Event::Handle<std::vector<TopJet> > h_topjetssoftdrop;


};

}
