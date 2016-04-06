#pragma once

#include <algorithm>
#include <cmath>

#include "TH2.h"

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Utils.h"

#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/GenTools.h"
#include <UHH2/common/include/TTbarGen.h>

using namespace std;
using namespace uhh2;

// namespace {


class TopPtWeight : public AnalysisModule {
public:
explicit TopPtWeight(uhh2::Context& ctx,
                     const std::string& ttgen_name,
                     float a, float b,
                     const std::string& weight_name="weight_ttbar",
                     bool apply_weight=true):
    h_ttbargen_(ctx.get_handle<TTbarGen>(ttgen_name)),
    h_weight_(ctx.get_handle<float>(weight_name)),
    a_(a), b_(b),
    apply_weight_(apply_weight) {}

    virtual bool process(uhh2::Event& event) override {

        if (event.isRealData) {
            return true;
        }

        const TTbarGen& ttbargen = event.get(h_ttbargen_);
        float wgt = 1.;

        if (ttbargen.DecayChannel() != TTbarGen::e_notfound) {

            float tpt1 = ttbargen.Top()    .v4().Pt();
            float tpt2 = ttbargen.Antitop().v4().Pt();

            tpt1 = std::min(tpt1, float(400.));
            tpt2 = std::min(tpt2, float(400.));

            wgt = sqrt(exp(a_+b_*tpt1)*exp(a_+b_*tpt2));
        }

        event.set(h_weight_, wgt);
        if (apply_weight_) {
            event.weight *= wgt;
        }

        return true;
    }

protected:
    uhh2::Event::Handle<TTbarGen> h_ttbargen_;
    uhh2::Event::Handle<float> h_weight_;
    float a_, b_;
    bool apply_weight_;
};  // TopPtWeight


class TopPtWeightHist: public Hists {
public:
    explicit TopPtWeightHist(Context & ctx,
                             const string & dirname,
                             const string & weight_name):
        Hists(ctx, dirname),
        h_weight_(ctx.get_handle<float>(weight_name)),
        hist(book<TH1F>("ttbar_reweight_n_events",
                        ";bin 0: no weight, bin 1: with weight;events",
                        2, -.5, 1.5)) {}

    virtual void fill(const Event & event) override {
        if (event.is_valid(h_weight_)) {

	  hist->Fill(0.);
	  hist->Fill(1., event.get(h_weight_));
        }
    }

private:
    uhh2::Event::Handle<float> h_weight_;
    TH1F * hist;
};
