/*-
 * Test 0005:	BPF_LD+BPF_H+BPF_ABS
 *
 * $FreeBSD: soc2013/dpl/head/tools/regression/bpf/bpf_filter/tests/test0005.h 182436 2008-08-28 18:38:55Z jkim $
 */

/* BPF program */
struct bpf_insn pc[] = {
	BPF_STMT(BPF_LD+BPF_H+BPF_ABS, 1),
	BPF_STMT(BPF_RET+BPF_A, 0),
};

/* Packet */
u_char	pkt[] = {
	0x01, 0x23, 0x45,
};

/* Packet length seen on wire */
u_int	wirelen =	sizeof(pkt);

/* Packet length passed on buffer */
u_int	buflen =	sizeof(pkt);

/* Invalid instruction */
int	invalid =	0;

/* Expected return value */
u_int	expect =	0x2345;

/* Expected signal */
int	expect_signal =	0;
