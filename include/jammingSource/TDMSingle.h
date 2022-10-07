/* -*- c++ -*- */
/*
 * Copyright 2022 mortarboard.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_TDMSINGLE_H
#define INCLUDED_JAMMINGSOURCE_TDMSINGLE_H

#include <gnuradio/jammingSource/api.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/fxpt_nco.h>

namespace gr {
namespace jammingSource {

/*!
 * \brief <+description of block+>
 * \ingroup jammingSource
 *
 */
class JAMMINGSOURCE_API TDMSingle : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<TDMSingle> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of jammingSource::TDMSingle.
     *
     * To avoid accidental use of raw pointers, jammingSource::TDMSingle's
     * constructor is in a private implementation
     * class. jammingSource::TDMSingle::make is the public interface for
     * creating new instances.
     */
    static sptr make(double sampling_freq,
                     std::string wave_freq,
                     double period);

    virtual double sampling_freq() const = 0;
    virtual double period() const = 0;

    /*!
     * Sets the sampling frequency of the signal.
     * \param sampling_freq sampling frequency
     */
    virtual void set_sampling_freq(double sampling_freq) = 0;

    /*!
     * Sets the frequency of a periodic signal.
     * \param frequency frequency of the signal
     */
    virtual void set_frequency(std::string frequency) = 0;

    /*!
     * Sets the period of a signal.
     * \param period period of the every loop
     */
    virtual void set_period(double period) = 0;

};

} // namespace jammingSource
} // namespace gr

#endif /* INCLUDED_JAMMINGSOURCE_TDMSINGLE_H */
