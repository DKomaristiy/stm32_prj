all: task

task_flash: task
	@$(MAKE) -C task flash

task: library
	@$(MAKE) -C task all

library:
	@$(MAKE) -C lib all

clean:
	@$(MAKE) -C task clean
	@$(MAKE) -C lib clean
