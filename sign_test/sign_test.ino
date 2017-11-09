
// 定義腳位
#define PIN_f 23
#define PIN_a 25
#define PIN_3 27
#define PIN_e 29
#define PIN_d 31
#define PIN_h 33
#define PIN_c 35
#define PIN_g 37
#define PIN_0 39
#define PIN_b 41
#define PIN_1 43
#define PIN_2 45

// 共有4個七段顯示器，分別由針腳PIN_0、PIN_1、PIN_2、PIN_3控制
// 七段顯示器裡有8個LED（包含小數點）
#define POS_NUM 4
#define SEG_NUM 8
const byte pos_pins[POS_NUM] = {PIN_0, PIN_1, PIN_2, PIN_3};
const byte seg_pins[SEG_NUM] = {PIN_a, PIN_b, PIN_c, PIN_d, PIN_e, PIN_f, PIN_g, PIN_h};

void setup() {



 
}
