#pragma once

#include <string>
#include <vector>

#include "davelog/message.h"
#include "davelog/styles.h"
#include "davelog/levels.h"

namespace dave::log {

class Subscriber_Base_c {
  public:
    void Log(const Message_c &m);

    explicit Subscriber_Base_c(
        LevelMask_c lm = LevelMask_c().All(),
        Style_e s = Style_e::pretty
    );

    void SetStyle(Style_e s) {
        style_ = s;
    };
    void Close();

    virtual ~Subscriber_Base_c() = default;

  protected:
    Style_e style_;
    LevelMask_c level_mask_;

    std::string ToJS(const Message_c &m) const;
    std::string ToPrettyDetails(const Message_c &m) const;
    std::string ToTightDetails(const Message_c &m) const;
    std::string ToPlain(const Message_c &m) const;

  private:
    virtual void LogInternal(const Message_c &m) = 0;
};

class Subscriber_FilePtr_c: public Subscriber_Base_c {
  public:
    explicit Subscriber_FilePtr_c(
        FILE *of,
        LevelMask_c lm = LevelMask_c().All(),
        Style_e s = Style_e::pretty
    );
    void Close();

  private:
    FILE *ofile_;
    void LogInternal(const Message_c &m) override;
};

}

