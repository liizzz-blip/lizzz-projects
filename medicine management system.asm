.model small
.stack 100h

.data
   input_password db 'Please enter your password: $'
   password db 'medica$'
   incorrect_password db 10,13,'Invalid password.$'

   welcome db 10,13,10,13,'Welcome to Medical Stores Management System$'
   msg1 db 10,13,10,13,'Choose an option of your choice:$'

   msg_medicines db 10,13,'Press 1 to buy medicines$'
   medicines_sold db 10,13,'Press 2 to view sold medicines statistics$'
   amount_print db 10,13,'Press 3 to view total earnings$'
   generate_receipt_option db 10,13,'Press 4 to generate a purchase receipt$'
   reset_system_option db 10,13,'Press 5 to reset system (Admin only)$'
   menu_exit_option db 10,13,'Press 6 to exit$'

   wrong_input db 10,13,'Invalid input. Please try again.$'
   input_again db 10,13,'Press one of the above options.$'   
   rs_suffix db 'rs$', 0     
   receipt_msg db 10,13,'Generating your purchase receipt...$', 0
   receipt_items db 10,13,'Items purchased:$', 0
   receipt_total db 10,13,'Total amount: $', 0  
   exit_message db 10, 13, 'Exiting the system. Thank you!$', 0


   newline db 10,13,'$', 0

   ; Medicine data (Updated prices)
   opt1 db 10,13,'1. Panadol - 50rs$'
   opt2 db 10,13,'2. Paracetamol - 100rs$'
   opt3 db 10,13,'3. Cleritek - 150rs$'
   opt4 db 10,13,'4. Aspirin - 200rs$'
   opt5 db 10,13,'5. Brufen - 250rs$'
   opt6 db 10,13,'6. Surbex Z - 300rs$'
   opt7 db 10,13,'7. Arinac - 50rs$'
   opt8 db 10,13,'8. Sinopharm Vaccine - 400rs$'
   opt9 db 10,13,'9. Pfizer Vaccine - 500rs$'

   purchased_msg db 10,13,'Medicine purchased successfully!$'

   ; Prices (Updated)
   price_panadol dw 50
   price_paracetamol dw 100
   price_cleritek dw 150
   price_aspirin dw 200
   price_brufen dw 250
   price_surbex dw 300
   price_arinac dw 50
   price_sinopharm dw 400
   price_pfizer dw 500


   panadol_sold db 0
   paracetamol_sold db 0
   cleritek_sold db 0
   aspirin_sold db 0
   brufen_sold db 0
   surbex_sold db 0
   arinac_sold db 0
   sinopharm_sold db 0
   pfizer_sold db 0

   ; Amount
   total_earnings dw 0

   ; Admin password
   admin_password db 'admin123$', 0
   admin_incorrect db 10,13,'Admin password incorrect.$'

   ; Miscellaneous
   reset_msg db 10,13,'System reset successfully.$'

   sold_statistics db 10,13,'Sold Statistics:$'
   stat_panadol db 10,13,'Panadol Sold: $'
   stat_paracetamol db 10,13,'Paracetamol Sold: $'
   stat_cleritek db 10,13,'Cleritek Sold: $'
   stat_aspirin db 10,13,'Aspirin Sold: $'
   stat_brufen db 10,13,'Brufen Sold: $'
   stat_surbex db 10,13,'Surbex Sold: $'
   stat_arinac db 10,13,'Arinac Sold: $'
   stat_sinopharm db 10,13,'Sinopharm Sold: $'
   stat_pfizer db 10,13,'Pfizer Sold: $' 

display_number proc
    ; Inputs:
    ; AX - Number to display
    ; BL - Suffix flag (1 = show "rs", 0 = no suffix)

    push ax            ; Save AX on the stack
    push dx            ; Save DX on the stack

    ; Handle special case for 0
    cmp ax, 0          ; Check if the number is 0
    jne skip_zero
    mov dl, '0'        ; Display '0'
    mov ah, 2
    int 21h
    jmp check_suffix   ; Skip conversion loop
skip_zero:

    ; Conversion: Number to ASCII
    xor cx, cx         ; Clear CX for digit count
convert_loop:
    xor dx, dx         ; Clear DX for division
    mov bx, 10         ; Divisor for base 10
    div bx             ; AX = AX / 10, DX = Remainder
    push dx            ; Push remainder (digit) onto stack
    inc cx             ; Increment digit count
    cmp ax, 0          ; Check if quotient is 0
    jne convert_loop   ; Repeat if not 0

    ; Display digits
display_loop:
    pop dx             ; Pop digit from stack
    add dl, '0'        ; Convert to ASCII
    mov ah, 2          ; DOS interrupt for character display
    int 21h            ; Display character
    loop display_loop  ; Loop until all digits are displayed

check_suffix:
    ; Check the suffix flag in BL
    cmp bl, 1          ; If BL == 1, display "rs"
    jne no_suffix
    mov dx, offset rs_suffix ; Display "rs"
    mov ah, 9
    int 21h
no_suffix:
    ; Restore registers
    pop dx
    pop ax
    ret
display_number endp


main proc
    mov ax,@data
    mov ds,ax

    ; Password authentication
    mov dx,offset input_password
    mov ah,9
    int 21h

    mov bx,offset password
    mov cx,6

l1:
    mov ah,1
    int 21h
    cmp al, [bx]
    jne incorrect
    inc bx
    loop l1  
   
start:
    mov dx,offset newline
    mov ah,9
    int 21h

    call menu
    mov dx,offset newline
    mov ah,9
    int 21h

    mov ah,1
    int 21h

    cmp al,'1'
    je buy_medicines
    cmp al,'2'
    je view_statistics
    cmp al,'3'
    je show_earnings
    cmp al,'4'
    je generate_receipt
    cmp al,'5'
    je reset_system
    cmp al,'6'
    je exit

    mov dx,offset wrong_input
    mov ah,9
    int 21h

    mov dx,offset input_again
    mov ah,9
    int 21h

    jmp start
    
ret
 

menu proc
    mov dx,offset welcome
    mov ah,9
    int 21h

    mov dx,offset msg1
    mov ah,9
    int 21h

    mov dx,offset msg_medicines
    mov ah,9
    int 21h

    mov dx,offset medicines_sold
    mov ah,9
    int 21h

    mov dx,offset amount_print
    mov ah,9
    int 21h

    mov dx,offset generate_receipt_option
    mov ah,9
    int 21h

    mov dx,offset reset_system_option
    mov ah,9
    int 21h

    mov dx,offset menu_exit_option
    mov ah,9
    int 21h

    ret
menu endp

buy_medicines proc
    ; Display available medicines
    mov dx, offset opt1
    mov ah, 9
    int 21h

    mov dx, offset opt2
    mov ah, 9
    int 21h

    mov dx, offset opt3
    mov ah, 9
    int 21h

    mov dx, offset opt4
    mov ah, 9
    int 21h

    mov dx, offset opt5
    mov ah, 9
    int 21h

    mov dx, offset opt6
    mov ah, 9
    int 21h

    mov dx, offset opt7
    mov ah, 9
    int 21h

    mov dx, offset opt8
    mov ah, 9
    int 21h

    mov dx, offset opt9
    mov ah, 9
    int 21h

    ; Ask user to select medicine
    mov dx, offset newline
    mov ah, 9
    int 21h
    mov dx, offset input_again
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h
    sub al, '0'       ; Convert ASCII to integer
    cmp al, 1
    je purchase_panadol
    cmp al, 2
    je purchase_paracetamol
    cmp al, 3
    je purchase_cleritek
    cmp al, 4
    je purchase_aspirin
    cmp al, 5
    je purchase_brufen
    cmp al, 6
    je purchase_surbex
    cmp al, 7
    je purchase_arinac
    cmp al, 8
    je purchase_sinopharm
    cmp al, 9
    je purchase_pfizer

    ; Invalid option
    mov dx, offset wrong_input
    mov ah, 9
    int 21h
    jmp start

purchase_panadol:
    inc panadol_sold                ; Increment sold count
    mov ax, total_earnings
    add ax, price_panadol           ; Add price to total earnings
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_paracetamol:
    inc paracetamol_sold
    mov ax, total_earnings
    add ax, price_paracetamol
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_cleritek:
    inc cleritek_sold
    mov ax, total_earnings
    add ax, price_cleritek
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_aspirin:
    inc aspirin_sold
    mov ax, total_earnings
    add ax, price_aspirin
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_brufen:
    inc brufen_sold
    mov ax, total_earnings
    add ax, price_brufen
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_surbex:
    inc surbex_sold
    mov ax, total_earnings
    add ax, price_surbex
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_arinac:
    inc arinac_sold
    mov ax, total_earnings
    add ax, price_arinac
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_sinopharm:
    inc sinopharm_sold
    mov ax, total_earnings
    add ax, price_sinopharm
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

purchase_pfizer:
    inc pfizer_sold
    mov ax, total_earnings
    add ax, price_pfizer
    mov total_earnings, ax
    mov dx, offset purchased_msg
    mov ah, 9
    int 21h
    jmp start

buy_medicines endp

view_statistics proc
    ; Display "Sold Statistics"
    mov dx, offset sold_statistics
    mov ah, 9
    int 21h

    ; Display each medicine sold count without "rs"
    mov dx, offset stat_panadol
    mov ah, 9
    int 21h
    xor ah, ah                ; Clear AH
    mov al, panadol_sold      ; Load Panadol sold count
    mov bl, 0                 ; Suppress "rs"
    call display_number

    mov dx, offset stat_paracetamol
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, paracetamol_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_cleritek
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, cleritek_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_aspirin
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, aspirin_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_brufen
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, brufen_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_surbex
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, surbex_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_arinac
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, arinac_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_sinopharm
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, sinopharm_sold
    mov bl, 0
    call display_number

    mov dx, offset stat_pfizer
    mov ah, 9
    int 21h
    xor ah, ah
    mov al, pfizer_sold
    mov bl, 0
    call display_number

    ; Return to the main menu
    jmp start
view_statistics endp

show_earnings proc
    mov dx, offset amount_print       ; "Press 3 to view total earnings"
    mov ah, 9
    int 21h

    mov dl, ':'                       ; Display colon
    mov ah, 2
    int 21h

    mov dl, ' '                       ; Add a space
    mov ah, 2
    int 21h

    mov ax, total_earnings            ; Load total earnings into AX
    mov bl, 1                         ; Enable "rs" suffix
    call display_number               ; Display total earnings with "rs"

    jmp start                         ; Return to the main menu
show_earnings endp



generate_receipt proc
    ; Display receipt header
    mov dx, offset receipt_msg       ; "Generating your purchase receipt..."
    mov ah, 9
    int 21h

    ; Display purchased items
    mov dx, offset receipt_items     ; "Items purchased:"
    mov ah, 9
    int 21h

    ; Check and display each purchased item
    mov al, panadol_sold             ; Panadol
    cmp al, 0
    je skip_panadol
    mov dx, offset opt1              ; Item name
    mov ah, 9
    int 21h
    mov dx, offset newline           ; Newline
    mov ah, 9
    int 21h
    xor ah, ah                       ; Clear AH
    call display_number              ; Display quantity sold
skip_panadol:

    mov al, paracetamol_sold         ; Paracetamol
    cmp al, 0
    je skip_paracetamol
    mov dx, offset opt2
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_paracetamol:

    mov al, cleritek_sold            ; Cleritek
    cmp al, 0
    je skip_cleritek
    mov dx, offset opt3
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_cleritek:

    mov al, aspirin_sold             ; Aspirin
    cmp al, 0
    je skip_aspirin
    mov dx, offset opt4
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_aspirin:

    mov al, brufen_sold              ; Brufen
    cmp al, 0
    je skip_brufen
    mov dx, offset opt5
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_brufen:

    mov al, surbex_sold              ; Surbex Z
    cmp al, 0
    je skip_surbex
    mov dx, offset opt6
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_surbex:

    mov al, arinac_sold              ; Arinac
    cmp al, 0
    je skip_arinac
    mov dx, offset opt7
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_arinac:

    mov al, sinopharm_sold           ; Sinopharm Vaccine
    cmp al, 0
    je skip_sinopharm
    mov dx, offset opt8
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_sinopharm:

    mov al, pfizer_sold              ; Pfizer Vaccine
    cmp al, 0
    je skip_pfizer
    mov dx, offset opt9
    mov ah, 9
    int 21h
    mov dx, offset newline
    mov ah, 9
    int 21h
    xor ah, ah
    mov ax, ax
    call display_number
skip_pfizer:

    ; Display total amount
    mov dx, offset receipt_total     ; "Total amount:"
    mov ah, 9
    int 21h
    mov ax, total_earnings           ; Load total earnings
    mov bl, 1
    call display_number              ; Display total amount with "rs"  
    

    mov dx, offset newline           ; Add a newline
    mov ah, 9
    int 21h

   jmp start
generate_receipt endp

reset_system proc
    ; Prompt for admin password
    mov dx, offset reset_system_option ; "Reset system (Admin only)"
    mov ah, 9
    int 21h

    mov dx, offset input_password      ; "Please enter your password:"
    mov ah, 9
    int 21h

    ; Compare entered password with admin_password
    lea si, admin_password             ; Load address of admin_password into SI
    mov cx, 8                          ; Length of the password (including $)
    mov bx, si                         ; Temporary BX to hold password comparison

password_loop:
    mov ah, 1                          ; Read single character input
    int 21h
    cmp al, [si]                       ; Compare entered character with admin_password
    jne incorrect_admin                ; If not equal, jump to incorrect_admin
    inc si                             ; Move to next character in admin_password
    loop password_loop                 ; Repeat for all characters

    ; If password matches
    mov panadol_sold, 0
    mov paracetamol_sold, 0
    mov cleritek_sold, 0
    mov aspirin_sold, 0
    mov brufen_sold, 0
    mov surbex_sold, 0
    mov arinac_sold, 0
    mov sinopharm_sold, 0
    mov pfizer_sold, 0
    mov total_earnings, 0              ; Reset total earnings

    mov dx, offset reset_msg           ; "System reset successfully."
    mov ah, 9
    int 21h
    jmp start                          ; Return to main menu

incorrect_admin:
    ; Display incorrect password message and return to menu
    mov dx, offset admin_incorrect     ; "Admin password incorrect."
    mov ah, 9
    int 21h
    jmp start                          ; Return to main menu

reset_system endp

exit proc
    ; Display the exit message
    mov dx, offset exit_message ; Load the address of the exit message
    mov ah, 9                   ; DOS interrupt to display string
    int 21h

    ; Exit the program
    mov ah, 4Ch                 ; DOS interrupt to terminate program
    int 21h
exit endp

incorrect:
    mov dx, offset incorrect_password
    mov ah, 9
    int 21h
    jmp exit

end main
    

