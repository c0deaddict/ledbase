#if LED_DIM == 2
#include "distortion_waves.h"

#include "FastLED.h" // only used for beatsin8

// https://editor.soulmatelights.com/gallery/1089-distorsion-waves

const uint8_t cos_wave[256] = {
0,   0,   0,   0,   1,   1,   1,   2,   2,   3,   4,   5,   6,   6,   8,
9,   10,  11,  12,  14,  15,  17,  18,  20,  22,  23,  25,  27,  29,  31,
33,  35,  38,  40,  42,  45,  47,  49,  52,  54,  57,  60,  62,  65,  68,
71,  73,  76,  79,  82,  85,  88,  91,  94,  97,  100, 103, 106, 109, 113,
116, 119, 122, 125, 128, 131, 135, 138, 141, 144, 147, 150, 153, 156, 159,
162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 191, 194, 197, 199, 202,
204, 207, 209, 212, 214, 216, 218, 221, 223, 225, 227, 229, 231, 232, 234,
236, 238, 239, 241, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 252,
253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253,
253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 241, 239, 238,
236, 234, 232, 231, 229, 227, 225, 223, 221, 218, 216, 214, 212, 209, 207,
204, 202, 199, 197, 194, 191, 189, 186, 183, 180, 177, 174, 171, 168, 165,
162, 159, 156, 153, 150, 147, 144, 141, 138, 135, 131, 128, 125, 122, 119,
116, 113, 109, 106, 103, 100, 97,  94,  91,  88,  85,  82,  79,  76,  73,
71,  68,  65,  62,  60,  57,  54,  52,  49,  47,  45,  42,  40,  38,  35,
33,  31,  29,  27,  25,  23,  22,  20,  18,  17,  15,  14,  12,  11,  10,
9,   8,   6,   6,   5,   4,   3,   2,   2,   1,   1,   1,   0,   0,   0,   0
};

void DistortionWaves::draw() {
    byte speed = 5;

    uint8_t w = 2;
    uint8_t scale = 4;

    uint16_t a = millis()/32;
    uint16_t a2 = a/2;
    uint16_t a3 = a/3;

    uint16_t cx =  beatsin8(10-speed,0,LED_XLEN)*scale;
    uint16_t cy =  beatsin8(12-speed,0,LED_YLEN)*scale;
    uint16_t cx1 = beatsin8(13-speed,0,LED_XLEN)*scale;
    uint16_t cy1 = beatsin8(15-speed,0,LED_YLEN)*scale;
    uint16_t cx2 = beatsin8(17-speed,0,LED_XLEN)*scale;
    uint16_t cy2 = beatsin8(14-speed,0,LED_YLEN)*scale;

    uint16_t xoffs=0;

    for (int x = 0; x < LED_XLEN; x++) {
         xoffs += scale;
         uint16_t yoffs = 0;

         for (int y = 0; y < LED_YLEN; y++) {
             yoffs += scale;

             byte rdistort = cos_wave [(cos_wave[((x<<3)+a )&255]+cos_wave[((y<<3)-a2)&255]+a3   )&255]>>1;
             byte gdistort = cos_wave [(cos_wave[((x<<3)-a2)&255]+cos_wave[((y<<3)+a3)&255]+a+32 )&255]>>1; 
             byte bdistort = cos_wave [(cos_wave[((x<<3)+a3)&255]+cos_wave[((y<<3)-a) &255]+a2+64)&255]>>1; 

             byte valueR = rdistort+ w*  (a- ( ((xoffs - cx) *  (xoffs - cx) +  (yoffs - cy) *   (yoffs - cy))>>7  ));
             byte valueG = gdistort+ w*  (a2-( ((xoffs - cx1) * (xoffs - cx1) + (yoffs - cy1) *  (yoffs - cy1))>>7 ));
             byte valueB = bdistort+ w*  (a3-( ((xoffs - cx2) * (xoffs - cx2) + (yoffs - cy2) *  (yoffs - cy2))>>7 ));

             valueR = cos_wave [(valueR)];
             valueG = cos_wave [(valueG)];
             valueB = cos_wave [(valueB)];

             leds->setPixel(x, y, RgbColor(valueR, valueG, valueB));
         }
    }
}

#endif
