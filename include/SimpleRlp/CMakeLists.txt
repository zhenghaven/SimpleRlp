# Copyright (c) 2022 Haofan Zheng
# Use of this source code is governed by an MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT.

file(GLOB headers_internal "Internal/*.hpp")

install(FILES ${headers_internal}
	DESTINATION include/SimpleRlp/Internal
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
