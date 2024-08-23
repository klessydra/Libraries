set(SOURCES
	src/external_input.c
	src/external_off.c
	src/input.c
	src/lay/layer0_bias.c
	src/lay/BASE_AC_EXT.c
	src/lay/BASE_B_EXT.c
	src/lay/layer1_filters.c
	src/lay/layer1_bias.c

	src/lay/layer2_filters.c
	src/lay/layer2_bias.c

	src/lay/layer4_filters.c
	src/lay/layer4_bias.c

	src/lay/layer5_filters.c
	src/lay/layer5_bias.c

	src/lay/layer7_filters.c
	src/lay/layer7_bias.c

	src/lay/layer8_filters.c
	src/lay/layer8_bias.c

	src/lay/layer9_filters.c
	src/lay/layer9_bias.c

	src/lay/layer11_filters.c
	src/lay/layer11_bias.c

	src/lay/layer12_filters.c
	src/lay/layer12_bias.c

	src/lay/layer13_filters.c
	src/lay/layer13_bias.c

 	src/lay/layer15_filters.c
 	src/lay/layer15_bias.c
	#
	src/lay/layer16_filters.c
	src/lay/layer16_bias.c
	#
	src/lay/layer17_filters.c
	src/lay/layer17_bias.c
	#
	 src/lay/layer19_filters.c
	 src/lay/layer19_bias.c
	#
	src/lay/layer20_filters.c
	src/lay/layer20_bias.c

	src/lay/layer21_filters.c
	src/lay/layer21_bias.c
	####################################################################################################################
	src/to_fixed.c
	src/softmax.c
	src/set_coord.c
	src/relu.c
	src/maxpool.c
	src/matrixReset.c
	src/getWeights.c
	src/getFeatures.c
	src/getBias.c
	src/fullyconnect.c
	src/displayResult.c
	src/cumulativeSum.c
	src/convolution2D.c
	src/convolution2D_SPM.c
	src/classifica.c
	src/addBias.c
	# src/dbg_functs.c
	####################################################################################################################
	src/duts/dut_matrix_L0_0.c
	src/duts/dut_matrix_L0_1.c
	src/duts/dut_matrix_L0_2.c
	src/duts/dut_matrix_L1_0.c
	src/duts/dut_matrix_L1_1.c
	src/duts/dut_matrix_L1_2.c	
	src/duts/dut_matrix_L1_3.c

	src/duts/dut_matrix_L2_0.c
	src/duts/dut_matrix_L2_1.c
	src/duts/dut_matrix_L2_2.c

	src/duts/dut_matrix_L2_0.c
	src/duts/dut_matrix_L2_1.c
	src/duts/dut_matrix_L2_2.c
	src/duts/dut_matrix_L2_3.c
	src/duts/dut_matrix_L2_4.c
	src/duts/dut_matrix_L2_5.c
	src/duts/dut_matrix_L2_6.c
	src/duts/dut_matrix_L2_7.c
	src/duts/dut_matrix_L2_8.c
	src/duts/dut_matrix_L2_9.c
	src/duts/dut_matrix_L2_10.c
	src/duts/dut_matrix_L2_11.c
	src/duts/dut_matrix_L2_12.c
	src/duts/dut_matrix_L2_13.c
	src/duts/dut_matrix_L2_14.c




	src/duts/dut_matrix_L3_0.c
	src/duts/dut_matrix_L3_1.c
	src/duts/dut_matrix_L3_2.c
	src/duts/dut_matrix_L4_0.c
	src/duts/dut_matrix_L4_1.c
	src/duts/dut_matrix_L4_2.c
	src/duts/dut_matrix_L5_0.c
	src/duts/dut_matrix_L5_1.c
	src/duts/dut_matrix_L5_2.c
	src/duts/dut_matrix_L5_3.c
	src/duts/dut_matrix_L5_4.c
	src/duts/dut_matrix_L5_5.c

	src/duts/dut_matrix_L6_0.c
	src/duts/dut_matrix_L6_1.c
	src/duts/dut_matrix_L6_2.c
	src/duts/dut_matrix_L7_0.c
	src/duts/dut_matrix_L7_1.c
	src/duts/dut_matrix_L7_2.c


	src/duts/dut_matrix_L8_0.c
	src/duts/dut_matrix_L8_1.c
	src/duts/dut_matrix_L8_2.c
	src/duts/dut_matrix_L8_3.c
	src/duts/dut_matrix_L8_4.c
	src/duts/dut_matrix_L8_5.c
	src/duts/dut_matrix_L8_6.c
	src/duts/dut_matrix_L8_7.c
	src/duts/dut_matrix_L8_8.c
	src/duts/dut_matrix_L8_9.c
	src/duts/dut_matrix_L8_10.c
	src/duts/dut_matrix_L8_11.c
	src/duts/dut_matrix_L8_12.c
	src/duts/dut_matrix_L8_13.c
	src/duts/dut_matrix_L8_14.c
	src/duts/dut_matrix_L8_15.c
	src/duts/dut_matrix_L8_16.c
	src/duts/dut_matrix_L8_17.c
	src/duts/dut_matrix_L8_18.c
	src/duts/dut_matrix_L8_19.c
	src/duts/dut_matrix_L8_20.c
	src/duts/dut_matrix_L8_21.c
	src/duts/dut_matrix_L8_22.c
	src/duts/dut_matrix_L8_23.c
	src/duts/dut_matrix_L8_24.c
	src/duts/dut_matrix_L8_25.c
	src/duts/dut_matrix_L8_26.c
	src/duts/dut_matrix_L8_27.c
	src/duts/dut_matrix_L8_28.c
	src/duts/dut_matrix_L8_29.c
	src/duts/dut_matrix_L8_30.c
	src/duts/dut_matrix_L8_31.c
	src/duts/dut_matrix_L8_32.c
	src/duts/dut_matrix_L8_33.c
	src/duts/dut_matrix_L8_34.c
	src/duts/dut_matrix_L8_35.c
	src/duts/dut_matrix_L8_36.c
	src/duts/dut_matrix_L8_37.c
	src/duts/dut_matrix_L8_38.c
	src/duts/dut_matrix_L8_39.c
	src/duts/dut_matrix_L8_40.c
	src/duts/dut_matrix_L8_41.c
	src/duts/dut_matrix_L8_42.c
	src/duts/dut_matrix_L8_43.c
	src/duts/dut_matrix_L8_44.c
	src/duts/dut_matrix_L8_45.c
	src/duts/dut_matrix_L8_46.c
	src/duts/dut_matrix_L8_47.c
	src/duts/dut_matrix_L8_48.c
	src/duts/dut_matrix_L8_49.c
	src/duts/dut_matrix_L8_50.c
	src/duts/dut_matrix_L8_51.c
	src/duts/dut_matrix_L8_52.c
	src/duts/dut_matrix_L8_53.c
	src/duts/dut_matrix_L8_54.c
	src/duts/dut_matrix_L8_55.c
	src/duts/dut_matrix_L8_56.c
	src/duts/dut_matrix_L8_57.c
	src/duts/dut_matrix_L8_58.c
	src/duts/dut_matrix_L8_59.c
	src/duts/dut_matrix_L8_60.c
	src/duts/dut_matrix_L8_61.c
	src/duts/dut_matrix_L8_62.c
	src/duts/dut_matrix_L8_63.c




	src/duts/dut_matrix_L9_0.c
	src/duts/dut_matrix_L9_1.c
	src/duts/dut_matrix_L9_2.c
	src/duts/dut_matrix_L9_3.c
	src/duts/dut_matrix_L9_4.c
	src/duts/dut_matrix_L9_5.c

	src/duts/dut_matrix_L10_0.c
	src/duts/dut_matrix_L10_1.c
	src/duts/dut_matrix_L10_2.c
	src/duts/dut_matrix_L11_0.c
	src/duts/dut_matrix_L11_1.c
	src/duts/dut_matrix_L11_2.c



src/duts/dut_matrix_L12_0.c
src/duts/dut_matrix_L12_1.c
src/duts/dut_matrix_L12_2.c
src/duts/dut_matrix_L12_3.c
src/duts/dut_matrix_L12_4.c
src/duts/dut_matrix_L12_5.c
src/duts/dut_matrix_L12_6.c
src/duts/dut_matrix_L12_7.c
src/duts/dut_matrix_L12_8.c
src/duts/dut_matrix_L12_9.c
src/duts/dut_matrix_L12_10.c
src/duts/dut_matrix_L12_11.c
src/duts/dut_matrix_L12_12.c
src/duts/dut_matrix_L12_13.c
src/duts/dut_matrix_L12_14.c
src/duts/dut_matrix_L12_15.c
src/duts/dut_matrix_L12_16.c
src/duts/dut_matrix_L12_17.c
src/duts/dut_matrix_L12_18.c
src/duts/dut_matrix_L12_19.c
src/duts/dut_matrix_L12_20.c
src/duts/dut_matrix_L12_21.c
src/duts/dut_matrix_L12_22.c
src/duts/dut_matrix_L12_23.c
src/duts/dut_matrix_L12_24.c
src/duts/dut_matrix_L12_25.c
src/duts/dut_matrix_L12_26.c
src/duts/dut_matrix_L12_27.c
src/duts/dut_matrix_L12_28.c
src/duts/dut_matrix_L12_29.c
src/duts/dut_matrix_L12_30.c
src/duts/dut_matrix_L12_31.c
src/duts/dut_matrix_L12_32.c
src/duts/dut_matrix_L12_33.c
src/duts/dut_matrix_L12_34.c
src/duts/dut_matrix_L12_35.c
src/duts/dut_matrix_L12_36.c
src/duts/dut_matrix_L12_37.c
src/duts/dut_matrix_L12_38.c
src/duts/dut_matrix_L12_39.c
src/duts/dut_matrix_L12_40.c
src/duts/dut_matrix_L12_41.c
src/duts/dut_matrix_L12_42.c
src/duts/dut_matrix_L12_43.c
src/duts/dut_matrix_L12_44.c
src/duts/dut_matrix_L12_45.c
src/duts/dut_matrix_L12_46.c
src/duts/dut_matrix_L12_47.c
src/duts/dut_matrix_L12_48.c
src/duts/dut_matrix_L12_49.c
src/duts/dut_matrix_L12_50.c
src/duts/dut_matrix_L12_51.c
src/duts/dut_matrix_L12_52.c
src/duts/dut_matrix_L12_53.c
src/duts/dut_matrix_L12_54.c
src/duts/dut_matrix_L12_55.c
src/duts/dut_matrix_L12_56.c
src/duts/dut_matrix_L12_57.c
src/duts/dut_matrix_L12_58.c
src/duts/dut_matrix_L12_59.c
src/duts/dut_matrix_L12_60.c
src/duts/dut_matrix_L12_61.c
src/duts/dut_matrix_L12_62.c
src/duts/dut_matrix_L12_63.c



 	src/duts/dut_matrix_L13_0.c
 	src/duts/dut_matrix_L13_1.c
 	src/duts/dut_matrix_L13_2.c

 	src/duts/dut_matrix_L14_0.c
	src/duts/dut_matrix_L14_1.c
	src/duts/dut_matrix_L14_2.c
#
 src/duts/dut_matrix_L15_0.c
 src/duts/dut_matrix_L15_1.c
 src/duts/dut_matrix_L15_2.c
# src/duts/dut_matrix_L15_3.c
# src/duts/dut_matrix_L15_4.c
# src/duts/dut_matrix_L15_5.c
# src/duts/dut_matrix_L15_6.c
# src/duts/dut_matrix_L15_7.c
# src/duts/dut_matrix_L15_8.c
# src/duts/dut_matrix_L15_9.c
# src/duts/dut_matrix_L15_10.c
# src/duts/dut_matrix_L15_11.c
# src/duts/dut_matrix_L15_12.c
# src/duts/dut_matrix_L15_13.c
# src/duts/dut_matrix_L15_14.c
#
# 
#
src/duts/dut_matrix_L16_0.c
src/duts/dut_matrix_L16_1.c
src/duts/dut_matrix_L16_2.c
src/duts/dut_matrix_L16_3.c
src/duts/dut_matrix_L16_4.c
src/duts/dut_matrix_L16_5.c
src/duts/dut_matrix_L16_6.c
src/duts/dut_matrix_L16_7.c
src/duts/dut_matrix_L16_8.c
src/duts/dut_matrix_L16_9.c
src/duts/dut_matrix_L16_10.c
src/duts/dut_matrix_L16_11.c
src/duts/dut_matrix_L16_12.c
src/duts/dut_matrix_L16_13.c
src/duts/dut_matrix_L16_14.c
src/duts/dut_matrix_L16_15.c

	src/duts/dut_matrix_L1600_0.c


 	src/duts/dut_matrix_L17_0.c
 	src/duts/dut_matrix_L17_1.c
 	src/duts/dut_matrix_L17_2.c
	src/duts/dut_matrix_L18_0.c 
 	src/duts/dut_matrix_L19_0.c
 	src/duts/dut_matrix_L20_0.c
 	src/duts/dut_matrix_L21_0.c
	##########################################################
)

set(HEADERS
    inc/Definitions_fully_test.h
    )

#set(CMAKE_C_COMPILER klessydra-unknown-elf-gcc)
#set(CMAKE_C_FLAGS -O3 -g)
include_directories(inc/)
add_library(kless_vgg_libs STATIC ${SOURCES} ${HEADERS})
