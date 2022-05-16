input [3:0] a;
input [3:0] b;

output equal;

wire bit_3_equal;
wire bit_2_equal;
wire bit_1_equal;
wire bit_0_equal;
wire bit_0_equal_1;
wire bit_2_equal_3;

assign bit_3_equal = a[3] ~^ b[3];
assign bit_2_equal = a[2] ~^ b[2];
assign bit_1_equal = a[1] ~^ b[1];
assign bit_0_equal = a[0] ~^ b[0];

assign bit_0_equal_1 = bit_1_equal & bit_0_equal;
assign bit_2_equal_3 = bit_3_equal & bit_2_equal;

assign equal = bit_0_equal_1 & bit_2_equal_3;
