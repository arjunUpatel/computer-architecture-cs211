input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire a_maxterm_01;
wire a_maxterm_04;

wire a_3_or_2;
wire a_1_or_not_0;
wire a_3_or_not_2;
wire a_1_or_0;

wire b_maxterm_05;
wire b_maxterm_06;

wire b_3_or_not_2;
wire b_1_or_not_0;
wire b_not_1_or_0;

wire c_maxterm_02;

wire c_3_or_2;
wire c_not_1_or_0;

wire d_maxterm_01;
wire d_maxterm_04;
wire d_maxterm_07;
wire d_maxterm_09;

wire d_maxterm_01_and_maxterm_04;
wire d_maxterm_07_and_maxterm_09;

wire d_3_or_2;
wire d_1_or_not_0;
wire d_3_or_not_2;
wire d_1_or_0;
wire d_not_1_or_not_0;
wire d_not_3_or_2;

wire e_minterm_00;
wire e_minterm_02;
wire e_minterm_06;
wire e_minterm_08;

wire e_minterm_00_or_minterm_02;
wire e_minterm_06_or_minterm_08;

wire e_not_3_and_not_2;
wire e_not_1_and_not_0;
wire e_1_and_not_0;
wire e_not_3_and_2;
wire e_3_and_not_2;

wire f_maxterm_01;
wire f_maxterm_02;
wire f_maxterm_03;
wire f_maxterm_07;

wire f_maxterm_01_and_maxterm_02;
wire f_maxterm_03_and_maxterm_07;

wire f_3_or_2;
wire f_1_or_not_0;
wire f_not_1_or_0;
wire f_not_1_or_not_0;
wire f_3_or_not_2;
wire f_not_1_or_not_0;

wire g_maxterm_01_and_maxterm_07;

wire g_maxterm_00;
wire g_maxterm_01;
wire g_maxterm_07;

wire g_3_or_2;
wire g_1_or_0;
wire g_1_or_not_0;
wire g_3_or_not_2;
wire g_not_1_or_not_0;

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign a_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign a_1_or_not_0 = numeral_bit[1] | not_numeral_bit_0;
assign a_3_or_not_2 = numeral_bit[3] | not_numeral_bit_2;
assign a_1_or_0 = numeral_bit[1] | numeral_bit[0];

assign a_maxterm_01 = a_3_or_2 | a_1_or_not_0;
assign a_maxterm_04 = a_3_or_not_2 | a_1_or_0;

assign a = a_maxterm_01 & a_maxterm_04;

assign b_3_or_not_2 = numeral_bit[3] | not_numeral_bit_2;
assign b_1_or_not_0 = numeral_bit[1] | not_numeral_bit_0;
assign b_not_1_or_0 = not_numeral_bit_1 | numeral_bit[0];

assign b_maxterm_05 = b_3_or_not_2 | b_1_or_not_0;
assign b_maxterm_06 = b_3_or_not_2 | b_not_1_or_0;

assign b = b_maxterm_05 & b_maxterm_06;

assign c_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign c_not_1_or_0 = not_numeral_bit_1 | numeral_bit[0];

assign c_maxterm_02 = c_3_or_2 | c_not_1_or_0;

assign c = c_maxterm_02;

assign d_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign d_1_or_not_0 = numeral_bit[1] | not_numeral_bit_0;
assign d_3_or_not_2  = numeral_bit[3] | not_numeral_bit_2;
assign d_1_or_0  = numeral_bit[1] | numeral_bit[0];
assign d_not_1_or_not_0 = not_numeral_bit_1 | not_numeral_bit_0;
assign d_not_3_or_2 = not_numeral_bit_3 | numeral_bit[2];

assign d_maxterm_01 = d_3_or_2 | d_1_or_not_0;
assign d_maxterm_04 = d_3_or_not_2 | d_1_or_0;
assign d_maxterm_07 = d_3_or_not_2 | d_not_1_or_not_0;
assign d_maxterm_09 = d_not_3_or_2 | d_1_or_not_0;

assign d_maxterm_01_and_maxterm_04 = d_maxterm_01 & d_maxterm_04;
assign d_maxterm_07_and_maxterm_09 = d_maxterm_07 & d_maxterm_09;

assign d = d_maxterm_01_and_maxterm_04 & d_maxterm_07_and_maxterm_09;

assign e_not_3_and_not_2 = not_numeral_bit_3 & not_numeral_bit_2;
assign e_not_1_and_not_0 = not_numeral_bit_1 & not_numeral_bit_0;
assign e_1_and_not_0 = numeral_bit[1] & not_numeral_bit_0;
assign e_not_3_and_2 = not_numeral_bit_3 & numeral_bit[2];
assign e_3_and_not_2 = numeral_bit[3] & not_numeral_bit_2;

assign e_minterm_00 = e_not_3_and_not_2 & e_not_1_and_not_0;
assign e_minterm_02 = e_not_3_and_not_2 & e_1_and_not_0;
assign e_minterm_06 = e_not_3_and_2 & e_1_and_not_0;
assign e_minterm_08 = e_3_and_not_2 & e_not_1_and_not_0;

assign e_minterm_00_or_minterm_02 = e_minterm_00 | e_minterm_02;
assign e_minterm_06_or_minterm_08 = e_minterm_06 | e_minterm_08;

assign e = e_minterm_00_or_minterm_02 | e_minterm_06_or_minterm_08;

assign f_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign f_1_or_not_0 = numeral_bit[1] | not_numeral_bit_0;
assign f_not_1_or_0 = not_numeral_bit_1 | numeral_bit[0];
assign f_not_1_or_not_0 = not_numeral_bit_1 | not_numeral_bit_0;
assign f_3_or_not_2 = numeral_bit[3] | not_numeral_bit_2;
assign f_not_1_or_not_0 = not_numeral_bit_1 | not_numeral_bit_0;

assign f_maxterm_01 = f_3_or_2 | f_1_or_not_0;
assign f_maxterm_02 = f_3_or_2 | f_not_1_or_0;
assign f_maxterm_03 = f_3_or_2 | f_not_1_or_not_0;
assign f_maxterm_07 = f_3_or_not_2 | f_not_1_or_not_0;

assign f_maxterm_01_and_maxterm_02 = f_maxterm_01 & f_maxterm_02;
assign f_maxterm_03_and_maxterm_07 = f_maxterm_03 & f_maxterm_07;

assign f = f_maxterm_01_and_maxterm_02 & f_maxterm_03_and_maxterm_07;

assign g_3_or_2 = numeral_bit[3] | numeral_bit[2];
assign g_1_or_0 = numeral_bit[1] | numeral_bit[0];
assign g_1_or_not_0 = numeral_bit[1] | not_numeral_bit_0;
assign g_3_or_not_2 = numeral_bit[3] | not_numeral_bit_2;
assign g_not_1_or_not_0 = not_numeral_bit_1 | not_numeral_bit_0;

assign g_maxterm_00 = g_3_or_2 | g_1_or_0;
assign g_maxterm_01 = g_3_or_2 | g_1_or_not_0;
assign g_maxterm_07 = g_3_or_not_2 | g_not_1_or_not_0;

assign g_maxterm_01_and_maxterm_07 = g_maxterm_01 & g_maxterm_07;

assign g = g_maxterm_00 & g_maxterm_01_and_maxterm_07;
