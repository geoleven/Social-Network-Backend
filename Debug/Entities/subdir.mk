################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Entities/edge.cpp \
../Entities/entities.cpp 

OBJS += \
./Entities/edge.o \
./Entities/entities.o 

CPP_DEPS += \
./Entities/edge.d \
./Entities/entities.d 


# Each subdirectory must supply rules for building sources it contributes
Entities/%.o: ../Entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


