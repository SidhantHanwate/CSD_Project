
module main(
    input clk,
    output [2:0] TMDSp, TMDSn,
    output TMDSp_clock, TMDSn_clock
);

    wire[31:0] dspAddr;
    wire [31:0] dspData;

// Instantiate displayMemory module
displayMemory displayMemory_inst (
    .clk(clk),
    .wr_en_display(1'b0),
    .byteWrite(1'b0),
    .half_wordWrite(1'b0),
    .full_wordWrite(1'b0),
    .writeAddress(32'd0),
    .writeData(32'd0),
    .displayAddr(dspAddr),
    .displayData(dspData)
);

// Instantiate HDMI_display module
HDMI_display HDMI_display_inst (
    .clk(clk),
    .displayData(dspData),
    .displayAddr(dspAddr),
    .TMDSp(TMDSp),
    .TMDSn(TMDSn),
    .TMDSp_clock(TMDSp_clock),
    .TMDSn_clock(TMDSn_clock)
);

endmodule
