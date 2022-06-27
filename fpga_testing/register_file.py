from typing import List

from nmigen import *
from nmigen.sim import *

from nmigen import Elaboratable,Module,Signal
from nmigen.build import Platform
from nmigen.cli import main_parser,main_runner
from nmigen.back import rtlil, verilog

class Register_file(Elaboratable):
    def __init__(self):
        #inputs
        self.load_Rs1_addr = Signal(5)
        self.load_Rs2_addr = Signal(5)
        self.load_csr_addr = Signal(12)
        self.write = Signal(1)
        self.write_csr = Signal(1)
        self.write_addr = Signal(5)
        self.write_data = Signal(32)
        self.write_csr_addr = Signal(12)
        self.temp_csr = Signal(32)

        #output 
        self.write_Rs1_data = Signal(32)
        self.write_Rs2_data = Signal(32)
        self.write_csr_data = Signal(32)
        self.reg_update = Array([Signal(1) for i in range(2**5)])

        self.reg = Array([Signal(signed(32)) for i in range(2**5)])

        self.csrs = Array([Signal(signed(32)) for i in range(2**1)])


    def elaborate(self,platform:Platform)->Module:
        m = Module()
        m.d.sync += self.csrs[Const(1)].eq(Const(5))
       
        # m.d.sync += self.reg[Const(1)].eq(0x00000001)

        with m.If(self.reg_update[Const(8)] == Const(0)):
            m.d.sync += self.reg[Const(8)].eq(0x00000011)

        with m.If(self.reg_update[Const(2)] == Const(0)):
            m.d.sync += self.reg[Const(2)].eq(Const(0x000003FF))
        #m.d.sync += self.reg[Const(7)].eq(0x00AABBCC)
        #m.d.sync += self.reg[Const(3)].eq(0x00000003)
       


        m.d.comb += self.write_Rs1_data.eq(self.reg[self.load_Rs1_addr])
        m.d.comb += self.write_Rs2_data.eq(self.reg[self.load_Rs2_addr])
        m.d.comb += self.write_csr_data.eq(self.csrs[self.load_csr_addr])
		
        with m.If(self.write):
            with m.If(self.write_csr):
                m.d.sync += self.reg[self.write_addr].eq(self.temp_csr)
            with m.Else():
                m.d.sync += self.reg[self.write_addr].eq(self.write_data)
                m.d.sync += self.reg_update[self.write_addr].eq(Const(1))
                self.write.eq(Const(0))
        with m.Else():
            m.d.sync += self.reg[Const(0)].eq(0)   

        with m.If(self.write_csr):
            m.d.sync += self.csrs[self.write_csr_addr].eq(self.write_data) 
        
        return m    

    def ports(self)->List[Signal]:
        return [self.load_Rs1_addr,
        self.load_Rs2_addr,
        self.write ,
        self.write_addr ,
        self.write_data ,
        self.write_Rs1_data ,
        self.write_Rs2_data] 

if(__name__=="__main__"):
    parser = main_parser()
    args = parser.parse_args()

    m = Module()
    pos = ClockDomain("pos", async_reset=True)
    neg = ClockDomain("neg",clk_edge="neg",async_reset=True)
    neg.clk = pos.clk

    m.domains += [pos,neg]
    m.submodules.Register_file = Register_file1 = Register_file()

    load_Rs1_addr = Signal(5)
    load_Rs2_addr = Signal(5)
    write = Signal(1)
    write_addr = Signal(5)
    write_data = Signal(32)

    m.d.pos += Register_file1.load_Rs1_addr.eq(load_Rs1_addr)
    m.d.pos += Register_file1.load_Rs2_addr.eq(load_Rs2_addr)
    m.d.neg += Register_file1.write.eq(write)
    m.d.neg += Register_file1.write_data.eq(write_addr)
    m.d.neg += Register_file1.write_data.eq(write_data)
			
    sim = Simulator(m)
    sim.add_clock(1e-6, domain="pos")
    def process1():
        yield write.eq(1)
        yield write_addr.eq(0b00100)
        yield write_data.eq(0x00000010)
        yield
        yield write.eq(1)
        yield write_addr.eq(0b00010)
        yield write_data.eq(0x00000001)
        yield 
        #yield load_Rs1_addr.eq(0b00010)
        #yield load_Rs2_addr.eq(0b00100)
        #yield 
    def process2():
        yield load_Rs1_addr.eq(0b00010)
        yield load_Rs2_addr.eq(0b00100)
        yield

        
#sim.add_sync_process(process1,domain="pos")
#sim.add_sync_process(process2,domain="neg")
#with sim.write_vcd("reg.vcd","reg.gtkw",traces=Register_file.ports()):
#	sim.run_until(100e-6, run_passive=True)

Wrapper  = Register_file()
frag = Wrapper.elaborate(platform=None)
#print(rtlil.convert(frag, ports=[sys.adr, sys.dat_r, sys.dat_w, sys.we]))
print(verilog.convert(frag, ports=Wrapper.ports()))

