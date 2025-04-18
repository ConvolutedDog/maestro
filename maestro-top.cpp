/******************************************************************************
Copyright (c) 2019 Georgia Instititue of Technology
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Author : Hyoukjun Kwon (hyoukjun@gatech.edu)
*******************************************************************************/

#include <iostream>
#include <memory>
#include <vector>

#include <boost/program_options.hpp>

#include "BASE_base-objects.hpp"
#include "option.hpp"

#include "API_configuration.hpp"
#include "API_user-interface-v2.hpp"

#include "utils.h"

int main(int argc, char **argv) {

  maestro::Options option;

  if (!option.parse(argc, argv)) {
    FANCY_EXIT_WITH_MESSAGE(1, "[MAESTRO] Failed to parse program options");
  }

  maestro::InitializeBaseObjects(option.message_print_lv);

  /*
   * Hard coded part; will Fix it
   */

  if (option.bw_sweep && option.top_bw_only) {
    // bw_tick is the step of bandwidth search during the DSE.
    // int min_bw = option.bw_tick;

    for (int bw = option.min_noc_bw; bw <= option.max_noc_bw;
         bw += option.bw_tick) {
      auto noc_multcast =
          std::make_shared<std::vector<bool>>();
      auto noc_latency =
          std::make_shared<std::vector<int>>();
      auto noc_bw =
          std::make_shared<std::vector<int>>();

      if (option.top_bw_only) {
        noc_bw->push_back(bw);
        noc_bw->push_back(70000);
        noc_bw->push_back(70000);
        noc_bw->push_back(70000);
        noc_bw->push_back(70000);
        noc_bw->push_back(70000);

        noc_latency->push_back(option.hop_latency * option.hops);
        noc_latency->push_back(1);
        noc_latency->push_back(1);
        noc_latency->push_back(1);
        noc_latency->push_back(1);
        noc_latency->push_back(1);

        noc_multcast->push_back(option.mc);
        noc_multcast->push_back(true);
        noc_multcast->push_back(true);
        noc_multcast->push_back(true);
        noc_multcast->push_back(true);
        noc_multcast->push_back(true);
      }

      auto config = std::make_shared<maestro::ConfigurationV2>(
          option.dfsl_file_name, option.hw_file_name, noc_bw, noc_latency,
          noc_multcast, option.np, option.num_simd_lanes, option.bw,
          option.l1_size, option.l2_size, option.offchip_bw);

      auto api = std::make_shared<maestro::APIV2>(config);
      auto res = api->AnalyzeNeuralNetwork(option.print_res_to_screen, true);
    }
  } else {
    auto noc_multcast =
        std::make_shared<std::vector<bool>>();
    auto noc_latency =
        std::make_shared<std::vector<int>>();
    auto noc_bw =
        std::make_shared<std::vector<int>>();

    // felix

    noc_bw->push_back(option.bw);
    noc_bw->push_back(option.bw);
    noc_bw->push_back(option.bw);
    noc_bw->push_back(option.bw);

    noc_latency->push_back(option.hop_latency * option.hops);
    noc_latency->push_back(option.hop_latency * option.hops);
    noc_latency->push_back(option.hop_latency * option.hops);
    noc_latency->push_back(option.hop_latency * option.hops);

    noc_multcast->push_back(true);
    noc_multcast->push_back(true);
    noc_multcast->push_back(true);
    noc_multcast->push_back(true);

    auto config = std::make_shared<maestro::ConfigurationV2>(
        option.dfsl_file_name, option.hw_file_name, noc_bw, noc_latency,
        noc_multcast, option.np, option.num_simd_lanes, option.bw,
        option.l1_size, option.l2_size, option.offchip_bw);

    auto api = std::make_shared<maestro::APIV2>(config);

    auto res = api->AnalyzeNeuralNetwork(option.print_res_to_screen,
                                         option.print_res_to_csv_file,
                                         option.print_log_file);
  }
  /////////////////////////////////////////////////////////////////

  return 0;
}
