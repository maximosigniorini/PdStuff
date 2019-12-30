// Setup routine for lib verbkit

#include "m_pd.h"

void combsL_tilde_setup(void);
void combsR_tilde_setup(void);
void damp_tilde_setup(void);
void dcombsL_tilde_setup(void);
void dcombsR_tilde_setup(void);
void diffusorL_tilde_setup(void);
void diffusorR_tilde_setup(void);

void verbkit_setup(void)
{
    post("verbkit version 1.0 by Katja Vetter, based on Jezar's freeverb");
    combsL_tilde_setup();
    combsR_tilde_setup();
    damp_tilde_setup();
    dcombsL_tilde_setup();
    dcombsR_tilde_setup();
    diffusorL_tilde_setup();
    diffusorR_tilde_setup();
}
