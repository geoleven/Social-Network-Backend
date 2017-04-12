################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Graph/bfs.cpp \
../Graph/dataInput.cpp \
../Graph/graph.cpp \
../Graph/mQuickSort.cpp 

OBJS += \
./Graph/bfs.o \
./Graph/dataInput.o \
./Graph/graph.o \
./Graph/mQuickSort.o 

CPP_DEPS += \
./Graph/bfs.d \
./Graph/dataInput.d \
./Graph/graph.d \
./Graph/mQuickSort.d 


# Each subdirectory must supply rules for building sources it contributes
Graph/%.o: ../Graph/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


