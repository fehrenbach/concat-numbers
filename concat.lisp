(defun base10-format (a b)
  (format nil "~d~d" a b))

(defun base2-format (a b)
  (format nil "~b~b" a b))

(defun base10-log-pow (a b)
  (declare (fixnum a b))
  (declare (optimize (safety 0) (speed 3)))
  (the fixnum
       (+ (the fixnum (* a (the fixnum (expt 10 (the fixnum (truncate (log b 10)))))))
          (the fixnum b))))

(defun base2-no-hints (a b)
  (logxor (ash a (integer-length b)) b))

(declaim (inline base2-lg-shift))
(defun base2-lg-shift (a b)
  (declare (type (unsigned-byte 32) a b))
  (declare (optimize (safety 0) (speed 3)))
  (the (unsigned-byte 32)
       (+ (ash a (integer-length b)) b)))

(declaim (inline base2-lg-shift-xor))
(defun base2-lg-shift-xor (a b)
  (declare (type (unsigned-byte 32) a b))
  (declare (optimize (safety 0) (speed 3)))
  (the (unsigned-byte 32)
       (logxor (ash a (integer-length b)) b)))

;; ; disassembly for BASE2-LG-SHIFT
;; ; Size: 32 bytes. Origin: #x1003C62EEF
;; ; EEF:       488BCF           MOV RCX, RDI                    ; no-arg-parsing entry point
;; ; EF2:       4883C901         OR RCX, 1
;; ; EF6:       480FBDC9         BSR RCX, RCX
;; ; EFA:       48D1FA           SAR RDX, 1
;; ; EFD:       48D3E2           SHL RDX, CL
;; ; F00:       48D1FF           SAR RDI, 1
;; ; F03:       4801FA           ADD RDX, RDI
;; ; F06:       48D1E2           SHL RDX, 1
;; ; F09:       488BE5           MOV RSP, RBP
;; ; F0C:       F8               CLC
;; ; F0D:       5D               POP RBP
;; ; F0E:       C3               RET

;; The SARs and SAL $something, 1 are for boxing and unboxing fixnums from/to (unsigned-byte 32), I think. Fixnums are tagged with 0, but I don't know at what end. If the tag is at the left side, we could just ignore it, because BSR won't find it. If it's on the right (least significant) side, we have to return (-1 BSR) or minus however many bits are used for tagging.

;; http://www.pvk.ca/Blog/2014/08/16/how-to-define-new-intrinsics-in-sbcl/
