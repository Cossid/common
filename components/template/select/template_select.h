#pragma once

#include "esphome/components/select/select.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/preferences.h"

#include "esphome/components/globals/globals_component.h"

namespace esphome {
namespace template_ {

class TemplateSelect : public select::Select, public PollingComponent {
 public:
  void set_template(std::function<optional<std::string>()> &&f) { this->f_ = f; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  Trigger<std::string> *get_set_trigger() const { return this->set_trigger_; }
  void set_optimistic(bool optimistic) { this->optimistic_ = optimistic; }
  void set_initial_option(const std::string &initial_option) { this->initial_option_ = initial_option; }
  void set_restore_value(bool restore_value) { this->restore_value_ = restore_value; }

  bool has_forced_hash = false;
  uint32_t forced_hash = 0;
  void set_forced_hash(uint32_t hash_value) {
    forced_hash = hash_value;
    has_forced_hash = true;
  }

  uint32_t forced_addr = 12345;
  void set_forced_addr(uint32_t addr_value) {
    forced_addr = addr_value;
  }

  bool has_global_forced_addr = false;
  globals::GlobalsComponent<int> *global_forced_addr;
  void set_global_addr(globals::GlobalsComponent<int> *ga_in) {
    has_global_forced_addr = true;
    global_forced_addr = ga_in;
  }

 protected:
  void control(const std::string &value) override;
  bool optimistic_ = false;
  std::string initial_option_;
  bool restore_value_ = false;
  Trigger<std::string> *set_trigger_ = new Trigger<std::string>();
  optional<std::function<optional<std::string>()>> f_;

  ESPPreferenceObject pref_;
};

}  // namespace template_
}  // namespace esphome
