/*****************************************************************************
 *                                McPAT
 *                      SOFTWARE LICENSE AGREEMENT
 *            Copyright 2009 Hewlett-Packard Development Company, L.P.
 *                          All Rights Reserved
 *
 * Permission to use, copy, and modify this software and its documentation is
 * hereby granted only under the following terms and conditions.  Both the
 * above copyright notice and this permission notice must appear in all copies
 * of the software, derivative works or modified versions, and any portions
 * thereof, and both notices must appear in supporting documentation.
 *
 * Any User of the software ("User"), by accessing and using it, agrees to the
 * terms and conditions set forth herein, and hereby grants back to Hewlett-
 * Packard Development Company, L.P. and its affiliated companies ("HP") a
 * non-exclusive, unrestricted, royalty-free right and license to copy,
 * modify, distribute copies, create derivate works and publicly display and
 * use, any changes, modifications, enhancements or extensions made to the
 * software by User, including but not limited to those affording
 * compatibility with other hardware or software, but excluding pre-existing
 * software applications that may incorporate the software.  User further
 * agrees to use its best efforts to inform HP of any such changes,
 * modifications, enhancements or extensions.
 *
 * Correspondence should be provided to HP at:
 *
 * Director of Intellectual Property Licensing
 * Office of Strategy and Technology
 * Hewlett-Packard Company
 * 1501 Page Mill Road
 * Palo Alto, California  94304
 *
 * The software may be further distributed by User (but not offered for
 * sale or transferred for compensation) to third parties, under the
 * condition that such third parties agree to abide by the terms and
 * conditions of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITH ANY AND ALL ERRORS AND DEFECTS
 * AND USER ACKNOWLEDGES THAT THE SOFTWARE MAY CONTAIN ERRORS AND DEFECTS.
 * HP DISCLAIMS ALL WARRANTIES WITH REGARD TO THE SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL
 * HP BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.
 *
 ***************************************************************************/

#ifndef __CACTI_INTERFACE_H__
#define __CACTI_INTERFACE_H__

#include "const.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#if NEW_BOOST
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#endif

using namespace std;

class min_values_t;
class mem_array;
class uca_org_t;

class powerComponents {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
public:
  double dynamic;
  double leakage;
  double gate_leakage;
  double short_circuit;

  powerComponents()
      : dynamic(0)
      , leakage(0)
      , gate_leakage(0)
      , short_circuit(0) {
  }
  powerComponents(const powerComponents &obj) {
    *this = obj;
  }
  powerComponents &operator=(const powerComponents &rhs) {
    dynamic       = rhs.dynamic;
    leakage       = rhs.leakage;
    gate_leakage  = rhs.gate_leakage;
    short_circuit = rhs.short_circuit;
    return *this;
  }
  void reset() {
    dynamic       = 0;
    leakage       = 0;
    gate_leakage  = 0;
    short_circuit = 0;
  }

  friend powerComponents operator+(const powerComponents &x, const powerComponents &y);
  friend powerComponents operator*(const powerComponents &x, double const *const y);
  double                 get_dyn() {
    return (dynamic + short_circuit);
  }
  double get_leak() {
    return (leakage + gate_leakage);
  }
};

class powerDef {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
public:
  powerComponents readOp;
  powerComponents writeOp;
  powerComponents searchOp; // Sheng: for CAM and FA

  powerDef()
      : readOp()
      , writeOp()
      , searchOp() {
  }
  void reset() {
    readOp.reset();
    writeOp.reset();
    searchOp.reset();
  }

  friend powerDef operator+(const powerDef &x, const powerDef &y);
  friend powerDef operator*(const powerDef &x, double const *const y);
};

class statsComponents {
public:
  double access;
  double hit;
  double miss;

  statsComponents()
      : access(0)
      , hit(0)
      , miss(0) {
  }
  statsComponents(const statsComponents &obj) {
    *this = obj;
  }
  statsComponents &operator=(const statsComponents &rhs) {
    access = rhs.access;
    hit    = rhs.hit;
    miss   = rhs.miss;
    return *this;
  }
  void reset() {
    access = 0;
    hit    = 0;
    miss   = 0;
  }

  friend statsComponents operator+(const statsComponents &x, const statsComponents &y);
  friend statsComponents operator*(const statsComponents &x, double const *const y);
};

class statsDef {
public:
  statsComponents readAc;
  statsComponents writeAc;
  statsComponents searchAc;

  statsDef()
      : readAc()
      , writeAc()
      , searchAc() {
  }
  void reset() {
    readAc.reset();
    writeAc.reset();
    searchAc.reset();
  }

  friend statsDef operator+(const statsDef &x, const statsDef &y);
  friend statsDef operator*(const statsDef &x, double const *const y);
};

enum Wire_type {
  Global /* gloabl wires with repeaters */,
  Global_5 /* 5% delay penalty */,
  Global_10 /* 10% delay penalty */,
  Global_20 /* 20% delay penalty */,
  Global_30 /* 30% delay penalty */,
  Low_swing /* differential low power wires with high area overhead */,
  Semi_global /* mid-level wires with repeaters*/,
  Transmission /* tranmission lines with high area overhead */,
  Optical /* optical wires */,
  Invalid_wtype
};

class InputParameter {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
public:
  void parse_cfg(const string &infile);

  bool error_checking(); // return false if the input parameters are problematic
  void display_ip();

  unsigned int cache_sz; // in bytes
  unsigned int line_sz;
  unsigned int assoc;
  unsigned int nbanks;
  unsigned int out_w; // == nr_bits_out
  bool         specific_tag;
  unsigned int tag_w;
  unsigned int access_mode;
  unsigned int obj_func_dyn_energy;
  unsigned int obj_func_dyn_power;
  unsigned int obj_func_leak_power;
  unsigned int obj_func_cycle_t;

  double       F_sz_nm; // feature size in nm
  double       F_sz_um; // feature size in um
  unsigned int num_rw_ports;
  unsigned int num_rd_ports;
  unsigned int num_wr_ports;
  unsigned int num_se_rd_ports;  // number of single ended read ports
  unsigned int num_search_ports; // Sheng: number of search ports for CAM
  bool         is_main_mem;
  bool         is_cache;
  bool         pure_ram;
  bool         pure_cam;
  bool         rpters_in_htree; // if there are repeaters in htree segment
  unsigned int ver_htree_wires_over_array;
  unsigned int broadcast_addr_din_over_ver_htrees;
  unsigned int temp;

  unsigned int ram_cell_tech_type;
  unsigned int peri_global_tech_type;
  unsigned int data_arr_ram_cell_tech_type;
  unsigned int data_arr_peri_global_tech_type;
  unsigned int tag_arr_ram_cell_tech_type;
  unsigned int tag_arr_peri_global_tech_type;

  unsigned int burst_len;
  unsigned int int_prefetch_w;
  unsigned int page_sz_bits;

  unsigned int   ic_proj_type;     // interconnect_projection_type
  unsigned int   wire_is_mat_type; // wire_inside_mat_type
  unsigned int   wire_os_mat_type; // wire_outside_mat_type
  enum Wire_type wt;
  int            force_wiretype;
  bool           print_input_args;
  unsigned int   nuca_cache_sz; // TODO
  int            ndbl, ndwl, nspd, ndsam1, ndsam2, ndcm;
  bool           force_cache_config;

  int cache_level;
  int cores;
  int nuca_bank_count;
  int force_nuca_bank;

  int delay_wt, dynamic_power_wt, leakage_power_wt, cycle_time_wt, area_wt;
  int delay_wt_nuca, dynamic_power_wt_nuca, leakage_power_wt_nuca, cycle_time_wt_nuca, area_wt_nuca;

  int delay_dev, dynamic_power_dev, leakage_power_dev, cycle_time_dev, area_dev;
  int delay_dev_nuca, dynamic_power_dev_nuca, leakage_power_dev_nuca, cycle_time_dev_nuca, area_dev_nuca;
  int ed; // ED or ED2 optimization
  int nuca;

  bool         fast_access;
  unsigned int block_sz; // bytes
  unsigned int tag_assoc;
  unsigned int data_assoc;
  bool         is_seq_acc;
  bool         fully_assoc;
  unsigned int nsets; // == number_of_sets
  int          print_detail;

  bool add_ecc_b_;
  // parameters for design constraint
  double throughput;
  double latency;
  bool   pipelinable;
  int    pipeline_stages;
  int    per_stage_vector;
  bool   with_clock_grid;
  float  freq;
};

typedef struct {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
  int      Ndwl;
  int      Ndbl;
  double   Nspd;
  int      deg_bl_muxing;
  int      Ndsam_lev_1;
  int      Ndsam_lev_2;
  int      number_activated_mats_horizontal_direction;
  int      number_subbanks;
  int      page_size_in_bits;
  double   delay_route_to_bank;
  double   delay_crossbar;
  double   delay_addr_din_horizontal_htree;
  double   delay_addr_din_vertical_htree;
  double   delay_row_predecode_driver_and_block;
  double   delay_row_decoder;
  double   delay_bitlines;
  double   delay_sense_amp;
  double   delay_subarray_output_driver;
  double   delay_bit_mux_predecode_driver_and_block;
  double   delay_bit_mux_decoder;
  double   delay_senseamp_mux_lev_1_predecode_driver_and_block;
  double   delay_senseamp_mux_lev_1_decoder;
  double   delay_senseamp_mux_lev_2_predecode_driver_and_block;
  double   delay_senseamp_mux_lev_2_decoder;
  double   delay_input_htree;
  double   delay_output_htree;
  double   delay_dout_vertical_htree;
  double   delay_dout_horizontal_htree;
  double   delay_comparator;
  double   access_time;
  double   cycle_time;
  double   multisubbank_interleave_cycle_time;
  double   delay_request_network;
  double   delay_inside_mat;
  double   delay_reply_network;
  double   trcd;
  double   cas_latency;
  double   precharge_delay;
  powerDef power_routing_to_bank;
  powerDef power_addr_input_htree;
  powerDef power_data_input_htree;
  powerDef power_data_output_htree;
  powerDef power_addr_horizontal_htree;
  powerDef power_datain_horizontal_htree;
  powerDef power_dataout_horizontal_htree;
  powerDef power_addr_vertical_htree;
  powerDef power_datain_vertical_htree;
  powerDef power_row_predecoder_drivers;
  powerDef power_row_predecoder_blocks;
  powerDef power_row_decoders;
  powerDef power_bit_mux_predecoder_drivers;
  powerDef power_bit_mux_predecoder_blocks;
  powerDef power_bit_mux_decoders;
  powerDef power_senseamp_mux_lev_1_predecoder_drivers;
  powerDef power_senseamp_mux_lev_1_predecoder_blocks;
  powerDef power_senseamp_mux_lev_1_decoders;
  powerDef power_senseamp_mux_lev_2_predecoder_drivers;
  powerDef power_senseamp_mux_lev_2_predecoder_blocks;
  powerDef power_senseamp_mux_lev_2_decoders;
  powerDef power_bitlines;
  powerDef power_sense_amps;
  powerDef power_prechg_eq_drivers;
  powerDef power_output_drivers_at_subarray;
  powerDef power_dataout_vertical_htree;
  powerDef power_comparators;
  powerDef power_crossbar;
  powerDef total_power;
  double   area;
  double   all_banks_height;
  double   all_banks_width;
  double   bank_height;
  double   bank_width;
  double   subarray_memory_cell_area_height;
  double   subarray_memory_cell_area_width;
  double   mat_height;
  double   mat_width;
  double   routing_area_height_within_bank;
  double   routing_area_width_within_bank;
  double   area_efficiency;
  //  double perc_power_dyn_routing_to_bank;
  //  double perc_power_dyn_addr_horizontal_htree;
  //  double perc_power_dyn_datain_horizontal_htree;
  //  double perc_power_dyn_dataout_horizontal_htree;
  //  double perc_power_dyn_addr_vertical_htree;
  //  double perc_power_dyn_datain_vertical_htree;
  //  double perc_power_dyn_row_predecoder_drivers;
  //  double perc_power_dyn_row_predecoder_blocks;
  //  double perc_power_dyn_row_decoders;
  //  double perc_power_dyn_bit_mux_predecoder_drivers;
  //  double perc_power_dyn_bit_mux_predecoder_blocks;
  //  double perc_power_dyn_bit_mux_decoders;
  //  double perc_power_dyn_senseamp_mux_lev_1_predecoder_drivers;
  //  double perc_power_dyn_senseamp_mux_lev_1_predecoder_blocks;
  //  double perc_power_dyn_senseamp_mux_lev_1_decoders;
  //  double perc_power_dyn_senseamp_mux_lev_2_predecoder_drivers;
  //  double perc_power_dyn_senseamp_mux_lev_2_predecoder_blocks;
  //  double perc_power_dyn_senseamp_mux_lev_2_decoders;
  //  double perc_power_dyn_bitlines;
  //  double perc_power_dyn_sense_amps;
  //  double perc_power_dyn_prechg_eq_drivers;
  //  double perc_power_dyn_subarray_output_drivers;
  //  double perc_power_dyn_dataout_vertical_htree;
  //  double perc_power_dyn_comparators;
  //  double perc_power_dyn_crossbar;
  //  double perc_power_dyn_spent_outside_mats;
  //  double perc_power_leak_routing_to_bank;
  //  double perc_power_leak_addr_horizontal_htree;
  //  double perc_power_leak_datain_horizontal_htree;
  //  double perc_power_leak_dataout_horizontal_htree;
  //  double perc_power_leak_addr_vertical_htree;
  //  double perc_power_leak_datain_vertical_htree;
  //  double perc_power_leak_row_predecoder_drivers;
  //  double perc_power_leak_row_predecoder_blocks;
  //  double perc_power_leak_row_decoders;
  //  double perc_power_leak_bit_mux_predecoder_drivers;
  //  double perc_power_leak_bit_mux_predecoder_blocks;
  //  double perc_power_leak_bit_mux_decoders;
  //  double perc_power_leak_senseamp_mux_lev_1_predecoder_drivers;
  //  double perc_power_leak_senseamp_mux_lev_1_predecoder_blocks;
  //  double perc_power_leak_senseamp_mux_lev_1_decoders;
  //  double perc_power_leak_senseamp_mux_lev_2_predecoder_drivers;
  //  double perc_power_leak_senseamp_mux_lev_2_predecoder_blocks;
  //  double perc_power_leak_senseamp_mux_lev_2_decoders;
  //  double perc_power_leak_bitlines;
  //  double perc_power_leak_sense_amps;
  //  double perc_power_leak_prechg_eq_drivers;
  //  double perc_power_leak_subarray_output_drivers;
  //  double perc_power_leak_dataout_vertical_htree;
  //  double perc_power_leak_comparators;
  //  double perc_power_leak_crossbar;
  //  double perc_leak_mats;
  //  double perc_active_mats;
  double refresh_power;
  double dram_refresh_period;
  double dram_array_availability;
  double dyn_read_energy_from_closed_page;
  double dyn_read_energy_from_open_page;
  double leak_power_subbank_closed_page;
  double leak_power_subbank_open_page;
  double leak_power_request_and_reply_networks;
  double activate_energy;
  double read_energy;
  double write_energy;
  double precharge_energy;
} results_mem_array;

class uca_org_t {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
public:
  mem_array *       tag_array2;
  mem_array *       data_array2;
  double            access_time;
  double            cycle_time;
  double            area;
  double            area_efficiency;
  powerDef          power;
  double            leak_power_with_sleep_transistors_in_mats;
  double            cache_ht;
  double            cache_len;
  char              file_n[100];
  double            vdd_periph_global;
  bool              valid;
  results_mem_array tag_array;
  results_mem_array data_array;

  void find_delay();
  void find_energy();
  void find_area();
  void find_cyc();

  std::vector<uca_org_t *> uca_q;
  uca_org_t *              uca_pg_reference;
  void                     cleanup();
};

uca_org_t cacti_interface(const string &infile_name);
uca_org_t cacti_interface(InputParameter *const local_interface);
uca_org_t init_interface(InputParameter *const local_interface);

uca_org_t cacti_interface(int cache_size, int line_size, int associativity, int rw_ports, int excl_read_ports, int excl_write_ports,
                          int single_ended_read_ports, int search_ports, int banks, double tech_node, int output_width,
                          int specific_tag, int tag_width, int access_mode, int cache, int main_mem, int obj_func_delay,
                          int obj_func_dynamic_power, int obj_func_leakage_power, int obj_func_area, int obj_func_cycle_time,
                          int dev_func_delay, int dev_func_dynamic_power, int dev_func_leakage_power, int dev_func_area,
                          int dev_func_cycle_time, int temp, int data_arr_ram_cell_tech_flavor_in,
                          int data_arr_peri_global_tech_flavor_in, int tag_arr_ram_cell_tech_flavor_in,
                          int tag_arr_peri_global_tech_flavor_in, int interconnect_projection_type_in, int wire_inside_mat_type_in,
                          int wire_outside_mat_type_in, int REPEATERS_IN_HTREE_SEGMENTS_in,
                          int VERTICAL_HTREE_WIRES_OVER_THE_ARRAY_in, int BROADCAST_ADDR_DATAIN_OVER_VERTICAL_HTREES_in,
                          int PAGE_SIZE_BITS_in, int BURST_LENGTH_in, int INTERNAL_PREFETCH_WIDTH_in, int force_wiretype,
                          int wiretype, int force_config, int ndwl, int ndbl, int nspd, int ndcm, int ndsam1, int ndsam2, int ecc);
//    int cache_size,
//    int line_size,
//    int associativity,
//    int rw_ports,
//    int excl_read_ports,
//    int excl_write_ports,
//    int single_ended_read_ports,
//    int banks,
//    double tech_node,
//    int output_width,
//    int specific_tag,
//    int tag_width,
//    int access_mode,
//    int cache,
//    int main_mem,
//    int obj_func_delay,
//    int obj_func_dynamic_power,
//    int obj_func_leakage_power,
//    int obj_func_area,
//    int obj_func_cycle_time,
//    int dev_func_delay,
//    int dev_func_dynamic_power,
//    int dev_func_leakage_power,
//    int dev_func_area,
//    int dev_func_cycle_time,
//    int temp,
//    int data_arr_ram_cell_tech_flavor_in,
//    int data_arr_peri_global_tech_flavor_in,
//    int tag_arr_ram_cell_tech_flavor_in,
//    int tag_arr_peri_global_tech_flavor_in,
//    int interconnect_projection_type_in,
//    int wire_inside_mat_type_in,
//    int wire_outside_mat_type_in,
//    int REPEATERS_IN_HTREE_SEGMENTS_in,
//    int VERTICAL_HTREE_WIRES_OVER_THE_ARRAY_in,
//    int BROADCAST_ADDR_DATAIN_OVER_VERTICAL_HTREES_in,
////    double MAXAREACONSTRAINT_PERC_in,
////    double MAXACCTIMECONSTRAINT_PERC_in,
////    double MAX_PERC_DIFF_IN_DELAY_FROM_BEST_DELAY_REPEATER_SOLUTION_in,
//    int PAGE_SIZE_BITS_in,
//    int BURST_LENGTH_in,
//    int INTERNAL_PREFETCH_WIDTH_in);

class mem_array {
#if NEW_BOOST
  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int version);
#endif
public:
  int      Ndwl;
  int      Ndbl;
  double   Nspd;
  int      deg_bl_muxing;
  int      Ndsam_lev_1;
  int      Ndsam_lev_2;
  double   access_time;
  double   cycle_time;
  double   multisubbank_interleave_cycle_time;
  double   area_ram_cells;
  double   area;
  powerDef power;
  double   delay_senseamp_mux_decoder;
  double   delay_before_subarray_output_driver;
  double   delay_from_subarray_output_driver_to_output;
  double   height;
  double   width;

  double delay_route_to_bank, delay_input_htree, delay_row_predecode_driver_and_block, delay_row_decoder, delay_bitlines,
      delay_sense_amp, delay_subarray_output_driver, delay_dout_htree, delay_comparator, delay_matchlines;

  double all_banks_height, all_banks_width, area_efficiency;

  powerDef power_routing_to_bank;
  powerDef power_addr_input_htree;
  powerDef power_data_input_htree;
  powerDef power_data_output_htree;
  powerDef power_htree_in_search;
  powerDef power_htree_out_search;
  powerDef power_row_predecoder_drivers;
  powerDef power_row_predecoder_blocks;
  powerDef power_row_decoders;
  powerDef power_bit_mux_predecoder_drivers;
  powerDef power_bit_mux_predecoder_blocks;
  powerDef power_bit_mux_decoders;
  powerDef power_senseamp_mux_lev_1_predecoder_drivers;
  powerDef power_senseamp_mux_lev_1_predecoder_blocks;
  powerDef power_senseamp_mux_lev_1_decoders;
  powerDef power_senseamp_mux_lev_2_predecoder_drivers;
  powerDef power_senseamp_mux_lev_2_predecoder_blocks;
  powerDef power_senseamp_mux_lev_2_decoders;
  powerDef power_bitlines;
  powerDef power_sense_amps;
  powerDef power_prechg_eq_drivers;
  powerDef power_output_drivers_at_subarray;
  powerDef power_dataout_vertical_htree;
  powerDef power_comparators;

  powerDef power_cam_bitline_precharge_eq_drv;
  powerDef power_searchline;
  powerDef power_searchline_precharge;
  powerDef power_matchlines;
  powerDef power_matchline_precharge;
  powerDef power_matchline_to_wordline_drv;

  min_values_t * arr_min;
  enum Wire_type wt;

  // dram stats
  double activate_energy, read_energy, write_energy, precharge_energy, refresh_power, leak_power_subbank_closed_page,
      leak_power_subbank_open_page, leak_power_request_and_reply_networks;

  double precharge_delay;

  static bool lt(const mem_array *m1, const mem_array *m2);
};

#endif
