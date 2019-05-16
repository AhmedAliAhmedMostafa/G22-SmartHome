//uDMA function set

// Enables the uDMA controller for use.
void uDMAEnable(void)
{
    // Set the master enable bit in the config register.
    HWREG(UDMA_CFG) = UDMA_CFG_MASTEN;
}

//Disables the uDMA controller for use.
void uDMADisable(void)
{
    
    // Clear the master enable bit in the config register.
    HWREG(UDMA_CFG) = 0;
}

//Gets the uDMA error status.
uint32_t uDMAErrorStatusGet(void)
{
  
    // Return the uDMA error status.
    return(HWREG(UDMA_ERRCLR));
}

//Clears the uDMA error interrupt.
void uDMAErrorStatusClear(void)
{
    //
    // Clear the uDMA error interrupt.
    //
    HWREG(UDMA_ERRCLR) = 1;
}

//Enables a uDMA channel for operation.
void
uDMAChannelEnable(uint32_t ui32ChannelNum)
{
    // Check the arguments.
    ASSERT((ui32ChannelNum & 0xffff) < 32);


    // Set the bit for this channel in the enable set register.
    HWREG(UDMA_ENASET) = 1 << (ui32ChannelNum & 0x1f);
}

//Disables a uDMA channel.
void uDMAChannelDisable(uint32_t ui32ChannelNum)
{
   
    // Check the arguments.
    ASSERT((ui32ChannelNum & 0xffff) < 32);
	
    // Set the bit for this channel in the enable clear register.
    HWREG(UDMA_ENACLR) = 1 << (ui32ChannelNum & 0x1f);
}

//Checks if a uDMA channel is enabled for operation.
bool uDMAChannelIsEnabled(uint32_t ui32ChannelNum)
{
    // Check the arguments.
    ASSERT((ui32ChannelNum & 0xffff) < 32);

    // AND the specified channel bit with the enable register and return the result.
    return((HWREG(UDMA_ENASET) & (1 << (ui32ChannelNum & 0x1f))) ? true : false);
}

//Sets the base address for the channel control table.
void uDMAControlBaseSet(void *psControlTable)
{
    // Check the arguments.
    ASSERT(((uint32_t)psControlTable & ~0x3FF) ==
           (uint32_t)psControlTable);
    ASSERT((uint32_t)psControlTable >= 0x20000000);

    // Program the base address into the register.
    HWREG(UDMA_CTLBASE) = (uint32_t)psControlTable;
}

//Gets the base address for the channel control table.
void * uDMAControlBaseGet(void)
{
    // Read the current value of the control base register and return it to the caller.
    return((void *)HWREG(UDMA_CTLBASE));
}

// Gets the base address for the channel control table alternate structures.
void *uDMAControlAlternateBaseGet(void)
{
    // Read the current value of the control base register and return it to the caller.
    return((void *)HWREG(UDMA_ALTBASE));
}

//Requests a uDMA channel to start a transfer.
void uDMAChannelRequest(uint32_t ui32ChannelNum)
{
    // Check the arguments.
    ASSERT((ui32ChannelNum & 0xffff) < 32);

    // Set the bit for this channel in the software uDMA request register.
    HWREG(UDMA_SWREQ) = 1 << (ui32ChannelNum & 0x1f);
}

//Enables attributes of a uDMA channel.
void uDMAChannelAttributeEnable(uint32_t ui32ChannelNum, uint32_t ui32Attr)
{
    // Check the arguments.
    ASSERT((ui32ChannelNum & 0xffff) < 32);
    ASSERT((ui32Attr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
                         UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    // In case a channel selector macro (like UDMA_CH0_USB0EP1RX) was
    // passed as the ui32ChannelNum parameter, extract just the channel number from this parameter.
    ui32ChannelNum &= 0x1f;

    // Set the useburst bit for this channel if set in ui32Config.
    if(ui32Attr & UDMA_ATTR_USEBURST)
    {
        HWREG(UDMA_USEBURSTSET) = 1 << ui32ChannelNum;
    }

    // Set the alternate control select bit for this channel, if set in ui32Config.
    if(ui32Attr & UDMA_ATTR_ALTSELECT)
    {
        HWREG(UDMA_ALTSET) = 1 << ui32ChannelNum;
    }

    // Set the high priority bit for this channel, if set in ui32Config.
    if(ui32Attr & UDMA_ATTR_HIGH_PRIORITY)
    {
        HWREG(UDMA_PRIOSET) = 1 << ui32ChannelNum;
    }

    // Set the request mask bit for this channel, if set in ui32Config.
    if(ui32Attr & UDMA_ATTR_REQMASK)
    {
        HWREG(UDMA_REQMASKSET) = 1 << ui32ChannelNum;
    }
}