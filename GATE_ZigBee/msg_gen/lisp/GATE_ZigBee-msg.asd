
(cl:in-package :asdf)

(defsystem "GATE_ZigBee-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "ZigbeeFrame" :depends-on ("_package_ZigbeeFrame"))
    (:file "_package_ZigbeeFrame" :depends-on ("_package"))
  ))