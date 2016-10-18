/* file: xpsASub.c
 * EPICS asub routines.
 * This asub is used to send numeric data via CA to a server.
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <dbDefs.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <epicsExport.h>

#ifndef MIN
#define MIN(a,b)        (((a)<(b))?(a):(b))
#endif

static long asubInit( aSubRecord* pr){
  printf( "asubInit: %s\n",pr->name);
  return(0);
}
static long asubConvert( aSubRecord* pr){
/*-----------------------------------------------------------------------------
 * This routine calculates m1 and m2 positions from phase and amplitude:
 * Inputs:	a	phase
 *		b	amplitude
 *		c	coefficient 1
 *		d	coefficient 2
 * Outputs:	vala	m1 position
 *		valb	m2 position
 * The formula is m1=-coeff1*p-a/2 and m2=-coeff1*p+a/2
 *  where p is phase and a is amplitude.
 *---------------------------------------------------------------------------*/
  float ph=(*(float*)pr->a);   float am=(*(float*)pr->b);
  float c1=(*(float*)pr->c);   float c2=(*(float*)pr->d);
  float* pm1=(float*)pr->vala; float* pm2=(float*)pr->valb;

  *pm1=c2-c1*ph-am/2;
  *pm2=c2-c1*ph+am/2;
//printf( "asubConvert: ph=%.2f,am=%.2f,c1=%.3f,c2=%.2f,m1=%f,m2=%f\n",
//ph,am,c1,c2,*pm1,*pm2);
  
  return(0);
}
static long asubMotToPhase( aSubRecord* pr){
/*-----------------------------------------------------------------------------
 * This routine calculates m1 and m2 positions from phase and amplitude:
 * Inputs:	a	m1 position
 *		b	m2 position
 *		c	coefficient 1
 *		d	coefficient 2
 * Outputs:	vala	phase
 *		valb	amplitude
 * The formulae are:
 *   p=(2*coeff2-m1-m2)/(2*coeff1)
 *   a=m2-m1
 *  where p is phase and a is amplitude.
 *---------------------------------------------------------------------------*/
  float m1=(*(float*)pr->a);   float m2=(*(float*)pr->b);
  float c1=(*(float*)pr->c);   float c2=(*(float*)pr->d);
  float* pph=(float*)pr->vala; float* pam=(float*)pr->valb;

  *pph=(2.0*c2-m1-m2)*0.5/c1;
  *pam=m2-m1;
//printf( "asubMotToPhase: m1=%.2f,m2=%.2f,c1=%.3f,c2=%.2f,ph=%f,am=%f\n",
//m1,m2,c1,c2,*pph,*pam);
  
  return(0);
}
epicsRegisterFunction( asubInit);
epicsRegisterFunction( asubConvert);
epicsRegisterFunction( asubMotToPhase);
