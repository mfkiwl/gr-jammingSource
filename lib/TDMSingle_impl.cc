/* -*- c++ -*- */
/*
 * Copyright 2022 mortarboard.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "TDMSingle_impl.h"
#include <gnuradio/io_signature.h>
#include <sstream>
namespace gr {
namespace jammingSource {

using output_type = gr_complex;
TDMSingle::sptr TDMSingle::make(double sampling_freq,
                     std::string wave_freq,
                     double period)
{
    return gnuradio::make_block_sptr<TDMSingle_impl>(sampling_freq, wave_freq,period);
}


/*
 * The private constructor
 */
TDMSingle_impl::TDMSingle_impl(double sampling_freq,
                    std::string wave_freq,
                    double period)
    : gr::sync_block("TDMSingle",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type))),
    d_sampling_freq(sampling_freq),
    d_period(period)
{
    set_frequency(wave_freq);
}

/*
 * Our virtual destructor.
 */
TDMSingle_impl::~TDMSingle_impl() {}

int TDMSingle_impl::work(int noutput_items,
                         gr_vector_const_void_star& input_items,
                         gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    gr_complex* optr = (gr_complex*)output_items[0];
    gr::thread::scoped_lock l(this->d_setlock);

    int out_nums = noutput_items;
    int cur_out_nums = 0;
    while(cur_out_nums<out_nums)
    {
        // the remaining samples needed to be produced
        int remain_out = out_nums - cur_out_nums;
        // samples need to be produced with current frequency
        int samples_of_cur_freq = std::min(d_sample_per_freq-d_cur_sample_count,remain_out);
        if(samples_of_cur_freq==0) throw std::runtime_error("jammingSource::TDMSingle: samples to be produced is zero!");
        
        // produce the samples
        d_nco.sincos(optr + cur_out_nums,samples_of_cur_freq,1);

        cur_out_nums += samples_of_cur_freq;
        d_cur_sample_count += samples_of_cur_freq;

        // switch to next frequency in d_frequency
        if(d_cur_sample_count >= d_sample_per_freq)
        {
            // set current frequency index
            d_cur_freq_index++;
            if(d_cur_freq_index >= d_frequency.size()) d_cur_freq_index = 0;

            d_nco.set_freq(d_frequency[d_cur_freq_index]);
            d_cur_sample_count = 0;
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

/*
 * Set central frequencies. 
 */
void TDMSingle_impl::set_frequency(std::string frequency)
{
    std::stringstream ss(frequency);
    
    // clear frequencies
    while(!d_frequency.empty()) d_frequency.erase(d_frequency.begin());

    // fill in d_frequency with new frequencies
    std::string temp;
    while(getline(ss,temp,','))
    {
        float temp_freq=std::stof(temp);
        d_frequency.push_back(temp_freq);
    }

    // set current frequency index
    d_cur_freq_index = 0;

    // reset samples of each frequency
    float samples_per_loop = float(d_period*d_sampling_freq); // set the samples per loop
    d_sample_per_freq = samples_per_loop / d_frequency.size();

    // set the current frequency count
    d_cur_sample_count = 0;
}

/*
 * Set sampling frequency
 */
void TDMSingle_impl::set_sampling_freq(double sampling_freq)
{
    d_sampling_freq = sampling_freq;
    
    // we need to reset others due to this change
    // set current frequency index
    d_cur_freq_index = 0;

    // reset samples of each frequency
    float samples_per_loop = float(d_period*d_sampling_freq); // set the samples per loop
    d_sample_per_freq = samples_per_loop / d_frequency.size();

    // set the current frequency count
    d_cur_sample_count = 0;
}

/*
 * Set loop period
 */
void TDMSingle_impl::set_period(double period)
{
    d_period = period;

    // we need to reset others due to this change
    // set current frequency index
    d_cur_freq_index = 0;

    // reset samples of each frequency
    float samples_per_loop = float(d_period*d_sampling_freq); // set the samples per loop
    d_sample_per_freq = samples_per_loop / d_frequency.size();

    // set the current frequency count
    d_cur_sample_count = 0;
    
} /* namespace jammingSource */
} /* namespace gr */
