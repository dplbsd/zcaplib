/*-
 * Test 0016:	BPF_JMP+BPF_JGT+BPF_K
 *
 * $FreeBSD: soc2013/dpl/head/tools/regression/bpf/bpf_filter/tests/test0016.h 182436 2008-08-28 18:38:55Z jkim $
 */

/* BPF program */
struct bpf_insn pc[] = {
	BPF_STMT(BPF_LD+BPF_IMM, 0x01234567),
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, 0x01234568, 2, 0),
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, 0x01234566, 2, 1),
	BPF_STMT(BPF_LD+BPF_IMM, 0xdeadc0de),
	BPF_STMT(BPF_RET+BPF_A, 0),
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, 0x01234567, 1, 0),
	BPF_STMT(BPF_LD+BPF_IMM, 0xc0decafe),
	BPF_STMT(BPF_RET+BPF_A, 0),
};

/* Packet */
u_char	pkt[] = {
	0x00,
};

/* Packet length seen on wire */
u_int	wirelen =	sizeof(pkt);

/* Packet length passed on buffer */
u_int	buflen =	sizeof(pkt);

/* Invalid instruction */
int	invalid =	0;

/* Expected return value */
u_int	expect =	0xc0decafe;

/* Expected signal */
int	expect_signal =	0;
