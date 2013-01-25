; Auto-generated. Do not edit!


(cl:in-package GATE_ZigBee-msg)


;//! \htmlinclude FrameSens.msg.html

(cl:defclass <FrameSens> (roslisp-msg-protocol:ros-message)
  ((seq
    :reader seq
    :initarg :seq
    :type cl:integer
    :initform 0)
   (stamp
    :reader stamp
    :initarg :stamp
    :type cl:real
    :initform 0)
   (capid
    :reader capid
    :initarg :capid
    :type cl:string
    :initform "")
   (caplocation
    :reader caplocation
    :initarg :caplocation
    :type cl:string
    :initform "")
   (sensvals
    :reader sensvals
    :initarg :sensvals
    :type cl:string
    :initform ""))
)

(cl:defclass FrameSens (<FrameSens>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FrameSens>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FrameSens)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name GATE_ZigBee-msg:<FrameSens> is deprecated: use GATE_ZigBee-msg:FrameSens instead.")))

(cl:ensure-generic-function 'seq-val :lambda-list '(m))
(cl:defmethod seq-val ((m <FrameSens>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GATE_ZigBee-msg:seq-val is deprecated.  Use GATE_ZigBee-msg:seq instead.")
  (seq m))

(cl:ensure-generic-function 'stamp-val :lambda-list '(m))
(cl:defmethod stamp-val ((m <FrameSens>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GATE_ZigBee-msg:stamp-val is deprecated.  Use GATE_ZigBee-msg:stamp instead.")
  (stamp m))

(cl:ensure-generic-function 'capid-val :lambda-list '(m))
(cl:defmethod capid-val ((m <FrameSens>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GATE_ZigBee-msg:capid-val is deprecated.  Use GATE_ZigBee-msg:capid instead.")
  (capid m))

(cl:ensure-generic-function 'caplocation-val :lambda-list '(m))
(cl:defmethod caplocation-val ((m <FrameSens>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GATE_ZigBee-msg:caplocation-val is deprecated.  Use GATE_ZigBee-msg:caplocation instead.")
  (caplocation m))

(cl:ensure-generic-function 'sensvals-val :lambda-list '(m))
(cl:defmethod sensvals-val ((m <FrameSens>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GATE_ZigBee-msg:sensvals-val is deprecated.  Use GATE_ZigBee-msg:sensvals instead.")
  (sensvals m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FrameSens>) ostream)
  "Serializes a message object of type '<FrameSens>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seq)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seq)) ostream)
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'stamp)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'stamp) (cl:floor (cl:slot-value msg 'stamp)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'capid))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'capid))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'caplocation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'caplocation))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'sensvals))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'sensvals))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FrameSens>) istream)
  "Deserializes a message object of type '<FrameSens>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'seq)) (cl:read-byte istream))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stamp) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'capid) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'capid) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'caplocation) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'caplocation) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'sensvals) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'sensvals) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FrameSens>)))
  "Returns string type for a message object of type '<FrameSens>"
  "GATE_ZigBee/FrameSens")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FrameSens)))
  "Returns string type for a message object of type 'FrameSens"
  "GATE_ZigBee/FrameSens")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FrameSens>)))
  "Returns md5sum for a message object of type '<FrameSens>"
  "3a4eba2d81702f284d03cceeefea0aac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FrameSens)))
  "Returns md5sum for a message object of type 'FrameSens"
  "3a4eba2d81702f284d03cceeefea0aac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FrameSens>)))
  "Returns full string definition for message of type '<FrameSens>"
  (cl:format cl:nil "uint32 seq~%time stamp~%string capid~%string caplocation~%string sensvals~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FrameSens)))
  "Returns full string definition for message of type 'FrameSens"
  (cl:format cl:nil "uint32 seq~%time stamp~%string capid~%string caplocation~%string sensvals~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FrameSens>))
  (cl:+ 0
     4
     8
     4 (cl:length (cl:slot-value msg 'capid))
     4 (cl:length (cl:slot-value msg 'caplocation))
     4 (cl:length (cl:slot-value msg 'sensvals))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FrameSens>))
  "Converts a ROS message object to a list"
  (cl:list 'FrameSens
    (cl:cons ':seq (seq msg))
    (cl:cons ':stamp (stamp msg))
    (cl:cons ':capid (capid msg))
    (cl:cons ':caplocation (caplocation msg))
    (cl:cons ':sensvals (sensvals msg))
))
