/* -*- c++ -*- */
/*
 * Copyright 2022 mortarboard.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_TDMSINGLE_IMPL_H
#define INCLUDED_JAMMINGSOURCE_TDMSINGLE_IMPL_H

#include <gnuradio/jammingSource/TDMSingle.h>

namespace gr {
namespace jammingSource {

class TDMSingle_impl : public TDMSingle
{
private:
    double d_sampling_freq;
    std::vector<float> d_frequency;
    double d_period;
    int d_cur_freq_index;
    int d_sample_per_freq;
    int d_cur_sample_count;
    gr::fxpt_nco d_nco;

public:
    TDMSingle_impl(double sampling_freq,
                    std::string wave_freq,
                    double period);
    ~TDMSingle_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    double sampling_freq() const override { return d_sampling_freq; }
    double period() const override { return d_period; }

    void set_sampling_freq(double sampling_freq) override;

    //set center frequencies of jamming signal
    void set_frequency(std::string frequency) override;
    void set_period(double period) override;

};

} // namespace jammingSource
} // namespace gr

#endif /* INCLUDED_JAMMINGSOURCE_TDMSINGLE_IMPL_H */
