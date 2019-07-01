((nil
  (eval . (set (make-local-variable 'flycheck-clang-include-path)
               (append flycheck-clang-include-path
                       (list (expand-file-name "./include")
                             (expand-file-name "./libft/include")))))))
	  ;; ((+cc-default-include-paths . (expand-file-name "./include") (expand-file-name "./libft/include")))
	  ;; ((flycheck-clang-include-paths . (expand-file-name "./include") (expand-file-name "./libft/include")))
	  ;; )))
