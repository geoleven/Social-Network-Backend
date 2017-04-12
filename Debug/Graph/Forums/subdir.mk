################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Graph/Forums/cpm.cpp \
../Graph/Forums/girvan_newman.cpp \
../Graph/Forums/topNForumsGraphs.cpp 

OBJS += \
./Graph/Forums/cpm.o \
./Graph/Forums/girvan_newman.o \
./Graph/Forums/topNForumsGraphs.o 

CPP_DEPS += \
./Graph/Forums/cpm.d \
./Graph/Forums/girvan_newman.d \
./Graph/Forums/topNForumsGraphs.d 


# Each subdirectory must supply rules for building sources it contributes
Graph/Forums/%.o: ../Graph/Forums/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


