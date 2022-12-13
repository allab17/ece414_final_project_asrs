#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=uart1.c main.c porta_in.c adc_intf.c ts_lcd.c tft_gfx.c tft_master.c glcdfont.c Touchscreen.c ztimer4.c timer1.c oc1_plib.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/uart1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/porta_in.o ${OBJECTDIR}/adc_intf.o ${OBJECTDIR}/ts_lcd.o ${OBJECTDIR}/tft_gfx.o ${OBJECTDIR}/tft_master.o ${OBJECTDIR}/glcdfont.o ${OBJECTDIR}/Touchscreen.o ${OBJECTDIR}/ztimer4.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/oc1_plib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/uart1.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/porta_in.o.d ${OBJECTDIR}/adc_intf.o.d ${OBJECTDIR}/ts_lcd.o.d ${OBJECTDIR}/tft_gfx.o.d ${OBJECTDIR}/tft_master.o.d ${OBJECTDIR}/glcdfont.o.d ${OBJECTDIR}/Touchscreen.o.d ${OBJECTDIR}/ztimer4.o.d ${OBJECTDIR}/timer1.o.d ${OBJECTDIR}/oc1_plib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/uart1.o ${OBJECTDIR}/main.o ${OBJECTDIR}/porta_in.o ${OBJECTDIR}/adc_intf.o ${OBJECTDIR}/ts_lcd.o ${OBJECTDIR}/tft_gfx.o ${OBJECTDIR}/tft_master.o ${OBJECTDIR}/glcdfont.o ${OBJECTDIR}/Touchscreen.o ${OBJECTDIR}/ztimer4.o ${OBJECTDIR}/timer1.o ${OBJECTDIR}/oc1_plib.o

# Source Files
SOURCEFILES=uart1.c main.c porta_in.c adc_intf.c ts_lcd.c tft_gfx.c tft_master.c glcdfont.c Touchscreen.c ztimer4.c timer1.c oc1_plib.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/uart1.o: uart1.c  .generated_files/flags/default/1da5d52f38e1da282d2d8c2a51e1801cc124c510 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1.o.d 
	@${RM} ${OBJECTDIR}/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart1.o.d" -o ${OBJECTDIR}/uart1.o uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/d698f3a21e133a46e575ee60330e3df4795ee572 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/porta_in.o: porta_in.c  .generated_files/flags/default/30dc58e8f289b19fbe21fe961464b8d2508e3837 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/porta_in.o.d 
	@${RM} ${OBJECTDIR}/porta_in.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/porta_in.o.d" -o ${OBJECTDIR}/porta_in.o porta_in.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/adc_intf.o: adc_intf.c  .generated_files/flags/default/e1b934c7d1110a845e74ae73fbddfeef9e6eb4f1 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_intf.o.d 
	@${RM} ${OBJECTDIR}/adc_intf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_intf.o.d" -o ${OBJECTDIR}/adc_intf.o adc_intf.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/ts_lcd.o: ts_lcd.c  .generated_files/flags/default/dcabee6cecfe0ba55c5f822ec91efd31b364d5b7 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ts_lcd.o.d 
	@${RM} ${OBJECTDIR}/ts_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ts_lcd.o.d" -o ${OBJECTDIR}/ts_lcd.o ts_lcd.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/tft_gfx.o: tft_gfx.c  .generated_files/flags/default/714e2be392128310f6cc5ede0ad4999c83c0e548 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tft_gfx.o.d 
	@${RM} ${OBJECTDIR}/tft_gfx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/tft_gfx.o.d" -o ${OBJECTDIR}/tft_gfx.o tft_gfx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/tft_master.o: tft_master.c  .generated_files/flags/default/7347bff9f1fd75bdb7423e78f57ccd8416140c41 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tft_master.o.d 
	@${RM} ${OBJECTDIR}/tft_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/tft_master.o.d" -o ${OBJECTDIR}/tft_master.o tft_master.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/glcdfont.o: glcdfont.c  .generated_files/flags/default/6bcfbca36fcef8d7ff61a4d688b89418957d1152 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/glcdfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/glcdfont.o.d" -o ${OBJECTDIR}/glcdfont.o glcdfont.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/Touchscreen.o: Touchscreen.c  .generated_files/flags/default/8ca72dc42872c2ac14d61044c0ee0f0137d70cd8 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Touchscreen.o.d 
	@${RM} ${OBJECTDIR}/Touchscreen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Touchscreen.o.d" -o ${OBJECTDIR}/Touchscreen.o Touchscreen.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/ztimer4.o: ztimer4.c  .generated_files/flags/default/b6cc116a477adb52c6f3e72b5f5d7c7cde5c1b71 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ztimer4.o.d 
	@${RM} ${OBJECTDIR}/ztimer4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ztimer4.o.d" -o ${OBJECTDIR}/ztimer4.o ztimer4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/timer1.o: timer1.c  .generated_files/flags/default/e9e24405c7d3f22874a8ea033d360f5245bed784 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/oc1_plib.o: oc1_plib.c  .generated_files/flags/default/c4cf21ccd301e10c8e42bf1c5d22f7b07d6bcf7b .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oc1_plib.o.d 
	@${RM} ${OBJECTDIR}/oc1_plib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oc1_plib.o.d" -o ${OBJECTDIR}/oc1_plib.o oc1_plib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
else
${OBJECTDIR}/uart1.o: uart1.c  .generated_files/flags/default/4354d8106527865d9c23a5f3a670576d2863ae22 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart1.o.d 
	@${RM} ${OBJECTDIR}/uart1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart1.o.d" -o ${OBJECTDIR}/uart1.o uart1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/ad1b6fddcd09df310ed6f69535bc550f5d40f337 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/porta_in.o: porta_in.c  .generated_files/flags/default/a80f0b96e0f366d38d382bd8db9895fbdf201584 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/porta_in.o.d 
	@${RM} ${OBJECTDIR}/porta_in.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/porta_in.o.d" -o ${OBJECTDIR}/porta_in.o porta_in.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/adc_intf.o: adc_intf.c  .generated_files/flags/default/d0cfb195e34548265f35461abd4a2750f8d269af .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc_intf.o.d 
	@${RM} ${OBJECTDIR}/adc_intf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_intf.o.d" -o ${OBJECTDIR}/adc_intf.o adc_intf.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/ts_lcd.o: ts_lcd.c  .generated_files/flags/default/c4799397dbdc1fe98cf31e9cfa0a3395276b28de .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ts_lcd.o.d 
	@${RM} ${OBJECTDIR}/ts_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ts_lcd.o.d" -o ${OBJECTDIR}/ts_lcd.o ts_lcd.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/tft_gfx.o: tft_gfx.c  .generated_files/flags/default/2d9a998fd90045a0fa40b7aad4ad4331b3c6190a .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tft_gfx.o.d 
	@${RM} ${OBJECTDIR}/tft_gfx.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/tft_gfx.o.d" -o ${OBJECTDIR}/tft_gfx.o tft_gfx.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/tft_master.o: tft_master.c  .generated_files/flags/default/f77ca5be4527973ebc662b57ca41d124816f4c99 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tft_master.o.d 
	@${RM} ${OBJECTDIR}/tft_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/tft_master.o.d" -o ${OBJECTDIR}/tft_master.o tft_master.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/glcdfont.o: glcdfont.c  .generated_files/flags/default/3149a91256b4b5badaaed349939bd4d921d2175c .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/glcdfont.o.d 
	@${RM} ${OBJECTDIR}/glcdfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/glcdfont.o.d" -o ${OBJECTDIR}/glcdfont.o glcdfont.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/Touchscreen.o: Touchscreen.c  .generated_files/flags/default/f62b780c8d0b32c59fae5d1ed50dc249fb166bb1 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Touchscreen.o.d 
	@${RM} ${OBJECTDIR}/Touchscreen.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Touchscreen.o.d" -o ${OBJECTDIR}/Touchscreen.o Touchscreen.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/ztimer4.o: ztimer4.c  .generated_files/flags/default/be68337ca46d228626350ae559f9591d8f11b002 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ztimer4.o.d 
	@${RM} ${OBJECTDIR}/ztimer4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ztimer4.o.d" -o ${OBJECTDIR}/ztimer4.o ztimer4.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/timer1.o: timer1.c  .generated_files/flags/default/c2508f055e089098f0828e330a44394e43beda06 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer1.o.d 
	@${RM} ${OBJECTDIR}/timer1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer1.o.d" -o ${OBJECTDIR}/timer1.o timer1.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
${OBJECTDIR}/oc1_plib.o: oc1_plib.c  .generated_files/flags/default/889f1152443c87b056169424ac5c838f0b816d71 .generated_files/flags/default/fa77e48c5d6b209b0dbc904325b3870195f7a677
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/oc1_plib.o.d 
	@${RM} ${OBJECTDIR}/oc1_plib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/oc1_plib.o.d" -o ${OBJECTDIR}/oc1_plib.o oc1_plib.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -D _SUPPRESS_PLIB_WARNING   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -D _SUPPRESS_PLIB_WARNING $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/final.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  -D _SUPPRESS_PLIB_WARNING $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/final.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
