#include "airfoil.hpp"
#include <IDKPhysics/shape/sphere.hpp>
#include <IDKPhysics/shape/OBB.hpp>
#include <libidk/idk_math.hpp>
#include <libidk/idk_random.hpp>


idk::Airfoil::Airfoil( idk::phys::World &world, float span, float chord )
:   m_world         (world),
    m_span          (4.0f*span),
    m_chord         (4.0f*chord),
    m_area          (m_span*m_chord),
    m_aspect_ratio  (glm::sqrt(m_span) / m_area),
    m_flap_ratio    (0.25f)

{
    // alpha    CL        CD       CDp       CM     Top_Xtr  Bot_Xtr
    //------ -------- --------- --------- -------- -------- --------
    m_data = {
        {-18.500,  -1.2258,    0},
        {-18.250,  -1.2456,    0},
        {-18.000,  -1.2659,    0},
        {-17.750,  -1.2852,    0},
        {-17.500,  -1.3031,    0},
        {-17.250,  -1.3193,    0},
        {-17.000,  -1.3322,    0},
        {-16.750,  -1.3427,    0},
        {-16.500,  -1.3519,    0},
        {-16.250,  -1.3687,    0},
        {-16.000,  -1.3806,    0},
        {-15.750,  -1.3868,    0},
        {-15.500,  -1.3879,    0},
        {-15.250,  -1.3854,    0},
        {-15.000,  -1.3802,    0},
        {-14.750,  -1.3739,    0},
        {-14.500,  -1.3669,    0},
        {-14.250,  -1.3590,    0},
        {-14.000,  -1.3502,    0},
        {-13.750,  -1.3399,    0},
        {-13.500,  -1.3281,    0},
        {-13.250,  -1.3149,    0},
        {-13.000,  -1.3132,    0},
        {-12.750,  -1.3004,    0},
        {-12.500,  -1.2834,    0},
        {-12.250,  -1.2649,    0},
        {-12.000,  -1.2455,    0},
        {-11.750,  -1.2250,    0},
        {-11.500,  -1.2032,    0},
        {-11.250,  -1.1872,    0},
        {-11.000,  -1.1666,    0},
        {-10.750,  -1.1449,    0},
        {-10.500,  -1.1228,    0},
        {-10.250,  -1.1000,    0},
        {-10.000,  -1.0807,    0},
        {-9.750,    1.0591,    0},
        {-9.500,    1.0368,    0},
        {-9.250,    1.0143,    0},
        {-9.000,    0.9948,    0},
        {-8.750,    0.9735,    0},
        {-8.500,    0.9517,    0},
        {-8.250,    0.9313,    0},
        {-8.000,    0.9104,    0},
        {-7.750,    0.8888,    0},
        {-7.500,    0.8687,    0},
        {-7.250,    0.8475,    0},
        {-7.000,    0.8268,    0},
        {-6.750,    0.7975,    0},
        {-6.500,    0.7634,    0},
        {-6.250,    0.7289,    0},
        {-6.000,    0.6939,    0},
        {-5.750,    0.6601,    0},
        {-5.500,    0.6268,    0},
        {-5.000,    0.5571,    0},
        {-4.750,    0.5213,    0},
        {-4.500,    0.4903,    0},
        {-4.250,    0.4588,    0},
        {-4.000,    0.4276,    0},
        {-3.750,    0.4004,    0},
        {-3.500,    0.3730,    0},
        {-3.250,    0.3462,    0},
        {-3.000,    0.3201,    0},
        {-2.750,    0.2938,    0},
        {-2.500,    0.2675,    0},
        {-2.250,    0.2410,    0},
        {-2.000,    0.2144,    0},
        {-1.750,    0.1878,    0},
        {-1.500,    0.1611,    0},
        {-1.250,    0.1343,    0},
        {-1.000,    0.1075,    0},
        {-0.750,    0.0806,    0},
        {-0.500,    0.0538,    0},
        {-0.250,    0.0268,    0},
        { 0.000,    0.0000,    0.00540},
        { 0.250,    0.0269,    0.00541},
        { 0.500,    0.0538,    0.00542},
        { 0.750,    0.0806,    0.00546},
        { 1.000,    0.1075,    0.00549},
        { 1.250,    0.1344,    0.00555},
        { 1.500,    0.1611,    0.00562},
        { 1.750,    0.1878,    0.00570},
        { 2.000,    0.2144,    0.00581},
        { 2.250,    0.2410,    0.00593},
        { 2.500,    0.2675,    0.00606},
        { 2.750,    0.2938,    0.00623},
        { 3.000,    0.3201,    0.00640},
        { 3.250,    0.3462,    0.00659},
        { 3.500,    0.3730,    0.00681},
        { 3.750,    0.4004,    0.00705},
        { 4.000,    0.4276,    0.00728},
        { 4.250,    0.4588,    0.00756},
        { 4.500,    0.4903,    0.00786},
        { 4.750,    0.5213,    0.00816},
        { 5.000,    0.5572,    0.00847},
        { 5.500,    0.6268,    0.00911},
        { 5.750,    0.6601,    0.00942},
        { 6.000,    0.6940,    0.00972},
        { 6.250,    0.7290,    0.01003},
        { 6.500,    0.7635,    0.01034},
        { 6.750,    0.7976,    0.01069},
        { 7.000,    0.8267,    0.01095},
        { 7.250,    0.8474,    0.01124},
        { 7.500,    0.8686,    0.01149},
        { 7.750,    0.8887,    0.01186},
        { 8.000,    0.9103,    0.01208},
        { 8.250,    0.9312,    0.01240},
        { 8.500,    0.9516,    0.01279},
        { 8.750,    0.9734,    0.01307},
        { 9.000,    0.9948,    0.01341},
        { 9.250,    1.0143,    0.01395},
        { 9.500,    1.0368,    0.01423},
        { 9.750,    1.0591,    0.01456},
        {10.000,    1.0808,    0.01499},
        {10.250,    1.1001,    0.01566},
        {10.500,    1.1229,    0.01602},
        {10.750,    1.1450,    0.01645},
        {11.000,    1.1668,    0.01690},
        {11.250,    1.1874,    0.01745},
        {11.500,    1.2033,    0.01840},
        {11.750,    1.2251,    0.01881},
        {12.000,    1.2457,    0.01931},
        {12.250,    1.2651,    0.01988},
        {12.500,    1.2837,    0.02049},
        {12.750,    1.3008,    0.02117},
        {13.000,    1.3137,    0.02207},
        {13.250,    1.3157,    0.02342},
        {13.500,    1.3290,    0.02415},
        {13.750,    1.3406,    0.02502},
        {14.000,    1.3509,    0.02602},
        {14.250,    1.3600,    0.02717},
        {14.500,    1.3679,    0.02848},
        {14.750,    1.3750,    0.02995},
        {15.000,    1.3814,    0.03158},
        {15.250,    1.3864,    0.03348},
        {15.500,    1.3892,    0.03575},
        {15.750,    1.3881,    0.03863},
        {16.000,    1.3818,    0.04235},
        {16.250,    1.3702,    0.04702},
        {16.500,    1.3536,    0.05261},
        {16.750,    1.3451,    0.05734},
        {17.000,    1.3352,    0.06237},
        {17.250,    1.3218,    0.06802},
        {17.500,    1.3059,    0.07416},
        {17.750,    1.2880,    0.08075},
        {18.000,    1.2685,    0.08773},
        {18.250,    1.2485,    0.09493},
        {18.500,    1.2284,    0.10229}
    };


    m_min_aoa = m_data.front()[0];
    m_max_aoa = m_data.back()[0];
}



std::pair<float, float>
idk::Airfoil::_sampleLiftDragCoefficients( float aoa )
{
    // idk_printvalue(aoa);
    aoa = glm::clamp(aoa, m_min_aoa, m_max_aoa);
    // idk_printvalue(aoa);

    float factor = (aoa - m_min_aoa) / (m_max_aoa - m_min_aoa);
    // idk_printvalue(factor);

    int   idx    = int(factor * (m_data.size()-1));
    // idk_printvalue(idx);
    // std::cout << "\n";

    float Cl = m_data[idx][1]; // lift coefficient
    float Cd = m_data[idx][2]; // drag coefficient

    return std::make_pair(Cl, Cd);
}


glm::vec3
idk::Airfoil::computeAeroForcesLinear( const glm::mat4 &parent, const glm::vec3 &pvel )
{
    auto &conf = m_world.config;

    static auto wind = glm::vec3(0.0f); // idk::randvec3(-0.2, +0.2);

    glm::mat4 T = glm::translate(glm::mat4(1.0f), localpos);
    glm::mat4 R = glm::mat4_cast(glm::angleAxis(wingAngle, glm::vec3(1, 0, 0)));

    transform = parent * T*R;
    worldpos = transform[3];
    // glm::vec3 vel = worldpos - prevpos;
    glm::vec3 vel = pvel;
    prevpos = worldpos;


    glm::vec3 airspeed = vel - wind;
    glm::vec3 front    = glm::mat3(transform) * glm::vec3(0, 0, 1);
    glm::vec3 right    = glm::mat3(transform) * glm::vec3(1, 0, 0);

    if (glm::length2(airspeed) == 0.0f)
    {
        return glm::vec3(0.0f);
    }

    // drag is parallel to relative wind.
    // lift is orthogonal to relative wind.
    glm::vec3 drag_dir = glm::normalize(-airspeed);
    glm::vec3 lift_dir = glm::cross(drag_dir, right);
    
    float cosTheta = glm::dot(drag_dir, -front);
    float theta    = glm::acos(cosTheta);
    float aoa      = glm::degrees(theta);

    if (aoa != glm::clamp(aoa, m_min_aoa, m_max_aoa))
    {
        return glm::vec3(0.0f);
    }

    // idk_printvalue(cosTheta);
    // idk_printvalue(theta);
    // idk_printvalue(aoa);

    float A = 1.0f; // wing area
    float p = conf.fluid_density;
    auto [Cl, Cd] = _sampleLiftDragCoefficients(aoa);

    if (m_flap_ratio > 0.0f)
    {

    }

    float efficiency_factor = 1.0f;
    float iCd = glm::sqrt(Cl) / (idk::PI * m_aspect_ratio * efficiency_factor);
    Cd += iCd;

    float dynamicP = 0.5f * glm::sqrt(glm::length(airspeed))
                   * conf.fluid_density * m_area;

    glm::vec3 lift = Cl * dynamicP * lift_dir;
    glm::vec3 drag = Cd * dynamicP * drag_dir;

    return -lift + drag;
}


glm::mat4
idk::Airfoil::getRenderMatrix( const glm::mat4 &parent )
{
    glm::mat4 T = glm::translate(glm::mat4(1.0f), localpos);
    glm::mat4 R = glm::mat4_cast(glm::angleAxis(wingAngle, glm::vec3(1, 0, 0)));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(m_span, 1.0f, m_chord));
    return parent * (T * R * S);
}
