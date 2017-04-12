################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Graph/Queries/query1.cpp \
../Graph/Queries/query2.cpp \
../Graph/Queries/query3.cpp \
../Graph/Queries/query4.cpp 

OBJS += \
./Graph/Queries/query1.o \
./Graph/Queries/query2.o \
./Graph/Queries/query3.o \
./Graph/Queries/query4.o 

CPP_DEPS += \
./Graph/Queries/query1.d \
./Graph/Queries/query2.d \
./Graph/Queries/query3.d \
./Graph/Queries/query4.d 


# Each subdirectory must supply rules for building sources it contributes
Graph/Queries/%.o: ../Graph/Queries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


