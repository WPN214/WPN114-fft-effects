#ifndef CONVOLVER_HPP
#define CONVOLVER_HPP

#include <wpn114audio/graph.hpp>
#include <external/fftconvolver/FFTConvolver.h>
#include <sndfile.h>

using namespace fftconvolver;
#define cnv_bsize 1024

//-------------------------------------------------------------------------------------------------
class Convolver : public Node
//-------------------------------------------------------------------------------------------------
{
    Q_OBJECT

    WPN_DECLARE_DEFAULT_AUDIO_INPUT     (audio_in, 2)
    WPN_DECLARE_DEFAULT_AUDIO_OUTPUT    (audio_out, 2)

    Q_PROPERTY (QString irPath READ ir_path WRITE set_ir_path )

public:
    //-------------------------------------------------------------------------------------------------
    Convolver()
    {

    }
    //-------------------------------------------------------------------------------------------------
    virtual
    ~Convolver() override
    //-------------------------------------------------------------------------------------------------
    {
        sf_close(m_file);

        delete m_convolver_l;
        delete m_convolver_r;

        for (nchannels_t n = 0; n < m_info.channels; ++n)
            delete[] m_buffer[n];

        delete[] m_buffer;
    }

    //-------------------------------------------------------------------------------------------------
    virtual void
    componentComplete() override
    //-------------------------------------------------------------------------------------------------
    {
        if (m_ir_path.isEmpty())
            return;

        m_file = sf_open(CSTR(m_ir_path), SFM_READ, &m_info);
        Node::componentComplete();
    }

    //-------------------------------------------------------------------------------------------------
    virtual void
    initialize(Graph::properties const& properties) override
    //-------------------------------------------------------------------------------------------------
    {
        m_buffer = new float*[m_info.channels]();

        for (nchannels_t n = 0; n < m_info.channels; ++n)
             m_buffer[n] = new float[m_info.frames];

        if (m_info.channels == 1)
            sf_readf_float(m_file, m_buffer[0], m_info.frames);

        else
        {
            // create temporary recipient
            float* tmp = new float[m_info.frames]();
            sf_readf_float(m_file, m_buffer[0], m_info.frames);

            // deinterleave buffer
            for (size_t f = 0; f < m_info.frames; ++f)
                for (nchannels_t c = 0; c < m_info.channels; ++c)
                    m_buffer[c][f] = *tmp++;

            delete[] tmp;
        }

        m_convolver_l = new FFTConvolver;
        m_convolver_r = new FFTConvolver;

        m_convolver_l->init(cnv_bsize, m_buffer[0], m_info.frames);

        if (m_info.channels == 1)
             m_convolver_r->init(cnv_bsize, m_buffer[0], m_info.frames);
        else m_convolver_r->init(cnv_bsize, m_buffer[1], m_info.frames);
    }

    //-------------------------------------------------------------------------------------------------
    virtual void
    rwrite(pool& inputs, pool& outputs, vector_t nframes) override
    //-------------------------------------------------------------------------------------------------
    {
        auto audio_in = inputs.audio[0];
        auto audio_out = outputs.audio[0];

        m_convolver_l->process(audio_in[0], audio_out[0], nframes);
        m_convolver_r->process(audio_in[1], audio_out[1], nframes);
    }

    //-------------------------------------------------------------------------------------------------
    QString
    ir_path() const { return m_ir_path; }

    //-------------------------------------------------------------------------------------------------
    void
    set_ir_path(QString path) { m_ir_path = path; }

private:

    SF_INFO
    m_info;

    SNDFILE*
    m_file = nullptr;

    FFTConvolver*
    m_convolver_l = nullptr;

    FFTConvolver*
    m_convolver_r = nullptr;

    float**
    m_buffer = nullptr;

    QString
    m_ir_path;
};

#endif // CONVOLVER_HPP
