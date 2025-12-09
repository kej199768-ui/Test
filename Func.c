/*
 * Func.c
 *
 *  Created on: 2021. 4. 16.
 *      Author: poweryhs
 */

#include "Define.h"
#include "Parameter.h"
#include "StructDefine.h"
#include "Func.h"
#include <math.h>


/* line to line voltage transformation to Phase voltage*/
uvw L2LtoPhase(uvw_LL* in)  //선간전압을 위상전압(?)으로
{
    uvw out;

    out.u = (in->uv - in->wu) * INV3;
    out.v = (in->vw - in->uv) * INV3;
    out.w = (in->wu - in->vw) * INV3;

    return out;
}


/* park transformation function*/
dq park_calc(dq* in, double angle)
{
    dq  out;

    out.d = in->d * cos(angle) + in->q * sin(angle);
    out.q = in->q * cos(angle) - in->d * sin(angle);

    return out;
}/* end of park_calc()*/

/* inverse park transformation function*/
dq ipark_calc(dq* in, double angle)
{
    dq  out;

    out.d = in->d * cos(angle) - in->q * sin(angle);
    out.q = in->q * cos(angle) + in->d * sin(angle);
    return out;
}/* end of ipark_calc()*/

/* clacke transformation function*/
dq clacke_calc(uvw* in)
{
    dq  out;

    out.d = in->u;
    out.q = (in->u + 2 * in->v) * 0.57735026918963;  // 1/sqrt(3) = 0.57735026918963
    return out;
}/* end of clacke_calc()*/

/* inverse clacke transformation function*/
uvw iclacke_calc(dq* in)
{
    uvw out;

    out.u = in->d;
    out.v = -0.5 * (in->d - SQRT3 * in->q);
    out.w = -(out.u + out.v);
    return out;
}/* end of iclacke_calc()*/


uvw Negative_Seq(uvw* in, uvw* in_APF)
{
    uvw out;

    //Negative sequence
    out.u = (in->u - 0.5 * in->v - 0.5 * in->w) * 0.33333333333 - 0.288675 * (in_APF->v - in_APF->w);
    out.v = (in->v - 0.5 * in->w - 0.5 * in->u) * 0.33333333333 - 0.288675 * (in_APF->w - in_APF->u);
    out.w = (in->w - 0.5 * in->u - 0.5 * in->v) * 0.33333333333 - 0.288675 * (in_APF->u - in_APF->v);

    return out;
}

uvw Zero_Seq(uvw* in, uvw* in_APF)
{
    uvw out;

    //Negative sequence
    out.u = (in->u + in->v + in->w) * 0.33333333333;
    out.v = (-0.5 * in->v - 0.5 * in->w - 0.5 * in->u) * 0.33333333333 - 0.288675 * (in_APF->u + in_APF->v + in_APF->w);
    out.w = (-0.5 * in->w - 0.5 * in->u - 0.5 * in->v) * 0.33333333333 + 0.288675 * (in_APF->u + in_APF->v + in_APF->w);

    return out;
}


/* Space Vector PWM calculation function*/
uvw SVPWM_calc(uvw* in)
{
    //  double  temp,Vdc_eff;
    double  Vmax, Vmin, Vsn;
    double  Van_ref, Vbn_ref, Vcn_ref;
    double  INV_Vdc = 0.;
    uvw out;

    //  Flag_on_off^=1;
    //  Flag_TF=Flag_on_off;

        // 3- element sort Algorithm (Vmax, Vmin)
    if ((in->u) > (in->v)) { Vmax = (in->u);    Vmin = (in->v); }
    else { Vmax = (in->v); Vmin = (in->u); }
    if ((in->w) > Vmax) Vmax = (in->w);
    if ((in->w) < Vmin) Vmin = (in->w);

    Vsn = -(Vmax + Vmin) * 0.5;
    Van_ref = (in->u) + Vsn;
    Vbn_ref = (in->v) + Vsn;
    Vcn_ref = (in->w) + Vsn;

    /*
        Vdc_eff=Vdc*(1-2*Tdead*INV_Ts);

        if((Vmax-Vmin)>Vdc_eff){
            temp = Vdc_eff/(Vmax-Vmin);
            Van_ref*=temp;
            Vbn_ref*=temp;
            Vcn_ref*=temp;
        }
    */
    /*
    if (Van_ref > Vdc_LPF * 0.5)    Van_ref = Vdc_LPF * 0.5;
    if (Van_ref < -Vdc_LPF * 0.5)   Van_ref = -Vdc_LPF * 0.5;
    if (Vbn_ref > Vdc_LPF * 0.5)    Vbn_ref = Vdc_LPF * 0.5;
    if (Vbn_ref < -Vdc_LPF * 0.5)   Vbn_ref = -Vdc_LPF * 0.5;
    if (Vcn_ref > Vdc_LPF * 0.5)    Vcn_ref = Vdc_LPF * 0.5;
    if (Vcn_ref < -Vdc_LPF * 0.5)   Vcn_ref = -Vdc_LPF * 0.5;

    INV_Vdc = 1. / Vdc_LPF;
    */
    /*  if(Van_ref>0) Van_ref=Van_ref - 0.015*Vdc_LPF;
        else Van_ref=Van_ref + 0.015*Vdc_LPF;
        if(Vbn_ref>0) Vbn_ref=Vbn_ref - 0.015*Vdc_LPF;
        else Vbn_ref=Vbn_ref + 0.015*Vdc_LPF;
        if(Vcn_ref>0) Vcn_ref=Vcn_ref - 0.015*Vdc_LPF;
        else Vcn_ref=Vcn_ref + 0.015*Vdc_LPF;
    */
    out.u = Ts * (0.5 + (Van_ref * INV_Vdc));   //Ta
    out.v = Ts * (0.5 + (Vbn_ref * INV_Vdc));   //Tb
    out.w = Ts * (0.5 + (Vcn_ref * INV_Vdc));   //Tc

    return out;

}/* end of SVPWM_calc()*/





/* PI control calculation function*/
void PI_Control_calc(PI_con *in)
{

    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki*in->Tsamp*(in->Err - in->Ka*(in->outtemp - in->out));
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Kp * in->Err * (1-in->Alpha) - in->Kp * in->Fdb* in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

}/* end of PI_Control_calc()*/

void PID_Control_calc(PID_con *in)
{
    //backward
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki*in->Tsamp*(in->Err - in->Ka*(in->outtemp - in->out));
    // DifferentagfiL Calculation
    in->Diff = in->Kd/in->Tsamp*(in->Err - in->Err1 );
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Diff + in->Kp * in->Err * (1-in->Alpha) - in->Kp * in->Fdb* in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

/*  //BgfiLinear
    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // PI(bgfiLinear)
    in->outtemp += (in->Kp+in->Ki*in->Tsamp)*in->Err - in->Ki*in->Err1;

    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;
*/
    in->Err1 = in->Err;

}/* end of PID_Control_calc()*/



void PIR_Control_calc(PIR_con *in, float Wres)
{

    // Error Calculation
    in->Err = in->Ref - in->Fdb;
    // Integral Calculation
    in->Integ += in->Ki*in->Tsamp*(in->Err - in->Ka*(in->outtemp - in->out));
    //  Resonant Calculation
    in->Res = RES((float)(Ts), Wres, 2*Wres, 1, in->Err, &in->Resfilter);
    // PI: Alpha=0, IP : Alpha=1
    in->Fb = in->Integ + in->Res + in->Kp * in->Err * (1-in->Alpha) - in->Kp * in->Fdb* in->Alpha;
    in->outtemp = in->Fb + in->FF;
    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

}/* end of PIR_Control_calc()*/


/* 1integrator + 1 pole + 2 zero control calculation function*/
void DPID_Control_calc(DPID_con *in)
{
    // Error Calculation for Negative Feedback
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    //Compensation Calculation
    in->outtemp = (1+in->Pole)*in->outtemp1 - in->Pole*in->outtemp2 + in->Kp*(in->Err - (in->Zero2 + in->Zero1)*in->Err1 + (in->Zero2 * in->Zero1)*in->Err2);
    in->out = in->outtemp + in->FF;
    in->out =((in->out) > (in->OutMax))?in->OutMax : ((in->out) < (in->OutMin))?in->OutMin : in->out;

    in->outtemp = in->out - in->FF;

    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;

}/* end of 2P1Z_Control_calc()*/


/* 2P1Z(1integrator+1pole+1zero) control calculation function*/
void TPOZ_Control_calc(TPOZ_con *in)
{
    float U1,U2;
    float Kptemp,K1,K2,K3;

    U1 = 8/(4+2*in->Wp*in->Tsamp);
    U2 = -(4-2*in->Wp*in->Tsamp)/(4+2*in->Wp*in->Tsamp);
    Kptemp = in->Kp*in->Tsamp/(4+2*in->Wp*in->Tsamp);
    K1 = in->Wz*in->Tsamp + 2;
    K2 = 2*in->Wz*in->Tsamp;
    K3 = in->Wz*in->Tsamp - 2;


    // Error Calculation for Negative Feedback
//  in->Err = in->Ref - in->Fdb - in->Ka*(in->outtemp - in->out);  //Anti-windup
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    // Error Calculation for Positive Feedback
//  in->Err = in->Fdb - in->Ref - in->Ka*(in->outtemp - in->out);  //Anti-windup
//  in->Err = in->Fdb - in->Ref;  //non Anti-windup

    //Compensation Calculation
    in->outtemp = U1*in->outtemp1 + U2*in->outtemp2 + Kptemp*(K1*in->Err + K2*in->Err1 + K3*in->Err2);

    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;


}/* end of 2P1Z_Control_calc()*/

/*void TPOZ_Control_calc(TPOZ_con *in)
{


    // Error Calculation for Negative Feedback
//  in->Err = in->Ref - in->Fdb - in->Ka*(in->outtemp - in->out);  //Anti-windup
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    // Error Calculation for Positive Feedback
//  in->Err = in->Fdb - in->Ref - in->Ka*(in->outtemp - in->out);  //Anti-windup
//  in->Err = in->Fdb - in->Ref;  //non Anti-windup

    //Compensation Calculation
//  in->outtemp = 1.017*in->outtemp1 - 0.01696*in->outtemp2 + in->Kp*(6.581*in->Err + 0.01906*in->Err1 - 6.562*in->Err2);   //65kHz sampling
//  in->outtemp = 0.778*in->outtemp1 + 0.222*in->outtemp2 + in->Kp*(8.188*in->Err + 0.03849*in->Err1 - 8.149*in->Err2);     //40kHz sampling Kp=4
//  in->outtemp = 0.9281*in->outtemp1 + 0.07193*in->outtemp2 + in->Kp*(1.831*in->Err + 0.0002952*in->Err1 - 1.83*in->Err2);     //40kHz sampling 1Hz zero Kp=20
//  in->outtemp = 0.9281*in->outtemp1 + 0.07193*in->outtemp2 + in->Kp*(0.917*in->Err + 0.01453*in->Err1 - 0.9204*in->Err2);     //40kHz sampling 100Hz zero Kp=40


    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;


}*//* end of 2P1Z_Control_calc()*/

/* 3P2Z(1integrator+2pole+2zero) control calculation function*/
void TPTZ_Control_calc(TPTZ_con *in)
{
    float Az,Bz,Cz,Dz,Ap,Bp,Cp,Dp;
    float U1,U2,U3;
//  float Kptemp,K1,K2,K3,K4;
    float Kptemp,K1,K2,K3;

    Az = 2 + in->Wz1*in->Tsamp;
    Bz = in->Wz1*in->Tsamp - 2;
    Cz = 2 + in->Wz2*in->Tsamp;
    Dz = in->Wz2*in->Tsamp - 2;

    Ap = 2 + in->Wp1*in->Tsamp;
    Bp = in->Wp1*in->Tsamp - 2;
    Cp = 2 + in->Wp2*in->Tsamp;
    Dp = in->Wp2*in->Tsamp - 2;

    U1 = (-Ap*Dp - Bp*Cp + Ap*Cp)/(Ap*Cp);
    U2 = (-Bp*Dp + Ap*Dp + Bp*Cp)/(Ap*Cp);
    U3 = (Bp*Dp)/(Ap*Cp);
    Kptemp = in->Kp*in->Tsamp*0.5*Az*Cz/(Ap*Cp);
    K1 = (Az*Dz + Bz*Cz + Az*Cz)/(Az*Cz);
    K2 = (Bz*Dz + Az*Dz + Bz*Cz)/(Az*Cz);
    K3 = (Bz*Dz)/(Az*Cz);

    // Error Calculation for Negative Feedback
//  in->Err = in->Ref - in->Fdb - in->Ka*(in->outtemp - in->out);  //Anti-windup
    in->Err = in->Ref - in->Fdb;  //non Anti-windup

    //Compensation Calculation
    in->outtemp = U1*in->outtemp1 + U2*in->outtemp2 + U3*in->outtemp3 + Kptemp*(in->Err + K1*in->Err1 + K2*in->Err2 + K3*in->Err3);
//  in->outtemp = 0.7131*in->outtemp1 + 0.5213*in->outtemp2 - 0.2345*in->outtemp3 + (0.273*in->Err - 0.2628*in->Err1 - 0.2729*in->Err2 + 0.2629*in->Err3);

    in->out =((in->outtemp) > (in->OutMax))?in->OutMax : ((in->outtemp) < (in->OutMin))?in->OutMin : in->outtemp;

    in->Err3 = in->Err2;
    in->Err2 = in->Err1;
    in->Err1 = in->Err;
    in->outtemp3 = in->outtemp2;
    in->outtemp2 = in->outtemp1;
    in->outtemp1 = in->outtemp;


}/* end of 3P2Z_Control_calc()*/




/* 1-order Low Pass filter function*/
float LPF1(float Tsamp, float fc, float in, filter1 *out)
{
    float Wc;
    float LPF1_A, LPF1_B, LPF1_C;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    LPF1_A = 2-Tsamp*Wc;
    LPF1_B = 2+Tsamp*Wc;
    LPF1_C = Tsamp*Wc;

    filter_out = (LPF1_A*out->output_old1)/LPF1_B;
    filter_in = LPF1_C*(in + out->input_old1)/LPF1_B;


    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old1 = out->output;
    out->input_old1 = in;

    return output1;

}/* end of LPF1*/

/* 2-order Low Pass filter function*/
float LPF2(float Tsamp, float fc, float zeta, float in, filter2 *out)
{
    float Wc;
    float LPF2_A, LPF2_B, LPF2_C, LPF2_D;
    float filter_in,filter_out;
    float output1;

    Wc = 2.*3.141593* fc;

    LPF2_A = 4 - 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    LPF2_B = 2*Wc*Wc*Tsamp*Tsamp-8;
    LPF2_C = 4 + 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    LPF2_D = Wc*Wc*Tsamp*Tsamp;


    filter_out = -(LPF2_A*out->output_old2 + LPF2_B*out->output_old1)/LPF2_C;
    filter_in = LPF2_D*(in + 2*out->input_old1+out->input_old2)/LPF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of LPF2()*/


/* 2-order High Pass filter function*/
float HPF2(float Tsamp, float fc, float zeta, float in, filter2 *out)
{
    float Wc;
    float HPF2_A, HPF2_B, HPF2_C, HPF2_D;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    HPF2_A = 4 - 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    HPF2_B = 2*Wc*Wc*Tsamp*Tsamp-8;
    HPF2_C = 4 + 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    HPF2_D = 4;


    filter_out = -(HPF2_A*out->output_old2 + HPF2_B*out->output_old1)/HPF2_C;
    filter_in = HPF2_D*(in - 2*out->input_old1+out->input_old2)/HPF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of HPF2()*/

/* 2-order Band Pass filter function*/
float BPF2(float Tsamp, float fc, float Band, float in, filter2 *out)
{
    float Wc;
    float BPF2_A, BPF2_B, BPF2_C, BPF2_D;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    BPF2_A = 4 - 2*Band*Tsamp + Wc*Wc*Tsamp*Tsamp;
    BPF2_B = 2*Wc*Wc*Tsamp*Tsamp-8;
    BPF2_C = 4 + 2*Band*Tsamp + Wc*Wc*Tsamp*Tsamp;
    BPF2_D = 2*Band*Tsamp;


    filter_out = -(BPF2_A*out->output_old2 + BPF2_B*out->output_old1)/BPF2_C;
    filter_in = BPF2_D*(in - out->input_old2)/BPF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;


    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of BPF2()*/

/* 2-order Band Stop filter function*/
float BSF2(float Tsamp, float fc, float Band, float in, filter2 *out)
{
    float Wc;
    float BSF2_A, BSF2_B, BSF2_C, BSF2_D;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    BSF2_A = 4 - 2*Band*Tsamp + Wc*Wc*Tsamp*Tsamp;
    BSF2_B = 2*Wc*Wc*Tsamp*Tsamp-8;
    BSF2_C = 4 + 2*Band*Tsamp + Wc*Wc*Tsamp*Tsamp;
    BSF2_D = 4+Wc*Wc*Tsamp*Tsamp;

    filter_out = -(BSF2_A*out->output_old2 + BSF2_B*out->output_old1)/BSF2_C;
    filter_in = (BSF2_D*in + BSF2_B*out->input_old1 + BSF2_D*out->input_old2)/BSF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of BSF2*/

/* 2-order Intergrate + High Pass filter function*/
float SBPF2(float Tsamp, float fc, float zeta, float in, filter2 *out)
{
    float Wc;
    float SBPF2_A, SBPF2_B, SBPF2_C, SBPF2_D;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    SBPF2_A = 4 - 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    SBPF2_B = 2*Wc*Wc*Tsamp*Tsamp-8;
    SBPF2_C = 4 + 4*zeta*Wc*Tsamp + Wc*Wc*Tsamp*Tsamp;
    SBPF2_D = 2*Tsamp;


    filter_out = -(SBPF2_A*out->output_old2 + SBPF2_B*out->output_old1)/SBPF2_C;
    filter_in = SBPF2_D*(in - out->input_old2)/SBPF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of SBPF2()*/

/* 2-order All Pass filter function*/
float APF2(float Tsamp, float fc, float in, filter2 *out)
{
    float Wc;
    float APF2_A, APF2_B, APF2_C;
    float filter_in,filter_out;
    float output1;

    Wc = 2*3.141593* fc;

    APF2_A = 4 - 2*Wc*Tsamp + PI*Tsamp*Tsamp/2;
    APF2_B = PI*Tsamp*Tsamp-8;
    APF2_C = 4 + 2*Wc*Tsamp + PI*Tsamp*Tsamp/2;

    filter_out = -(APF2_A*out->output_old2 + APF2_B*out->output_old1)/APF2_C;
    filter_in = out->input_old2 + (APF2_A*in + APF2_B*out->input_old1)/APF2_C;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}/* end of APF2()*/

float RES(float Tsamp, float Ws, float Kr, float h, float in, filter2 *out)
{
    float Res_A,Res_B,Res_C;
    float output1;
    float filter_in,filter_out;

    Res_A=Tsamp*Tsamp*h*h*Ws*Ws+4;
    Res_B=2*(Tsamp*Tsamp*h*h*Ws*Ws-4);
    Res_C=2*Kr*Tsamp;

    filter_out = -(Res_A*out->output_old2 + Res_B*out->output_old1)/Res_A;
    filter_in =  Res_C*(in - out->input_old2)/Res_A;

    out->output = filter_in + filter_out;
    output1 = out->output;

    out->output_old2 = out->output_old1;
    out->output_old1 = out->output;

    out->input_old2 = out->input_old1;
    out->input_old1 = in;

    return output1;

}
